/**
 * GameEngineCpp Documentation - Interactive Features
 */

document.addEventListener('DOMContentLoaded', () => {
    initNavigation();
    initScrollSpy();
    initInteractiveDiagrams();
    initCodeHighlighting();
    initAnimations();
    initSearch();
    initProgressIndicator();
});

/**
 * Navigation: Smooth scrolling and active link updates
 */
function initNavigation() {
    const navLinks = document.querySelectorAll('.nav-link');
    
    navLinks.forEach(link => {
        link.addEventListener('click', (e) => {
            const href = link.getAttribute('href');
            if (href.startsWith('#')) {
                e.preventDefault();
                const target = document.querySelector(href);
                if (target) {
                    target.scrollIntoView({ behavior: 'smooth' });
                }
            }
        });
    });
}

/**
 * Scroll spy: Updates active navigation based on scroll position
 */
function initScrollSpy() {
    const sections = document.querySelectorAll('.doc-section');
    const navLinks = document.querySelectorAll('.nav-link');
    
    const observerOptions = {
        root: null,
        rootMargin: '-20% 0px -70% 0px',
        threshold: 0
    };
    
    const observer = new IntersectionObserver((entries) => {
        entries.forEach(entry => {
            if (entry.isIntersecting) {
                const id = entry.target.getAttribute('id');
                navLinks.forEach(link => {
                    link.classList.remove('active');
                    if (link.getAttribute('href') === `#${id}`) {
                        link.classList.add('active');
                    }
                });
            }
        });
    }, observerOptions);
    
    sections.forEach(section => {
        observer.observe(section);
    });
}

/**
 * Interactive UML Diagrams with animations
 */
function initInteractiveDiagrams() {
    const diagrams = document.querySelectorAll('.uml-diagram');
    
    diagrams.forEach(diagram => {
        const elements = diagram.querySelectorAll('rect, circle, line');
        
        const observer = new IntersectionObserver((entries) => {
            entries.forEach(entry => {
                if (entry.isIntersecting) {
                    animateDiagramElements(elements);
                    observer.unobserve(entry.target);
                }
            });
        }, { threshold: 0.3 });
        
        observer.observe(diagram);
        
        elements.forEach(el => {
            if (el.tagName === 'rect' && el.classList.contains('uml-class')) {
                el.addEventListener('mouseenter', () => {
                    el.style.filter = 'brightness(1.2)';
                    el.style.cursor = 'pointer';
                });
                el.addEventListener('mouseleave', () => {
                    el.style.filter = '';
                });
            }
        });
    });
    
    addDiagramTooltips();
}

function animateDiagramElements(elements) {
    elements.forEach((el, index) => {
        el.style.opacity = '0';
        el.style.transform = 'translateY(10px)';
        
        setTimeout(() => {
            el.style.transition = 'opacity 0.4s ease, transform 0.4s ease';
            el.style.opacity = '1';
            el.style.transform = 'translateY(0)';
        }, index * 50);
    });
}

function addDiagramTooltips() {
    const umlClasses = document.querySelectorAll('.uml-class rect');
    
    umlClasses.forEach(rect => {
        const textEl = rect.parentElement.querySelector('.uml-title');
        if (textEl) {
            const className = textEl.textContent;
            
            rect.addEventListener('mouseenter', (e) => {
                showTooltip(e, className);
            });
            rect.addEventListener('mouseleave', hideTooltip);
            rect.addEventListener('mousemove', moveTooltip);
        }
    });
}

let tooltipEl = null;

function showTooltip(e, text) {
    if (!tooltipEl) {
        tooltipEl = document.createElement('div');
        tooltipEl.className = 'uml-tooltip';
        document.body.appendChild(tooltipEl);
    }
    tooltipEl.textContent = text;
    tooltipEl.style.opacity = '1';
    moveTooltip(e);
}

function hideTooltip() {
    if (tooltipEl) {
        tooltipEl.style.opacity = '0';
    }
}

function moveTooltip(e) {
    if (tooltipEl) {
        tooltipEl.style.left = `${e.clientX + 15}px`;
        tooltipEl.style.top = `${e.clientY + 15}px`;
    }
}

/**
 * Syntax highlighting for code blocks
 * CLion-inspired color scheme
 */
function initCodeHighlighting() {
    const codeBlocks = document.querySelectorAll('.code-block code');
    
    codeBlocks.forEach(block => {
        if (block.dataset.highlighted === 'true') return;
        
        const code = block.textContent;
        const highlighted = highlightCode(code);
        block.innerHTML = highlighted;
        block.dataset.highlighted = 'true';
    });
}

function escapeHtml(text) {
    return text
        .replace(/&/g, '&amp;')
        .replace(/</g, '&lt;')
        .replace(/>/g, '&gt;');
}

function highlightCode(code) {
    const lines = code.split('\n');
    
    return lines.map(line => {
        const tokens = tokenizeLine(line);
        
        return tokens.map(token => {
            if (token.type === 'comment') {
                return `<span class="hl-comment">${escapeHtml(token.text)}</span>`;
            }
            if (token.type === 'filename') {
                return `<span class="hl-type">${escapeHtml(token.text)}</span>`;
            }
            if (token.type === 'angle') {
                return `<span class="hl-angle">&lt;</span>${highlightAngleContent(token.text.slice(1, -1))}<span class="hl-angle">&gt;</span>`;
            }
            if (token.type === 'string') {
                return `<span class="hl-string">${escapeHtml(token.text)}</span>`;
            }
            if (token.type === 'preprocessor') {
                return `<span class="hl-preprocessor">${escapeHtml(token.text)}</span>`;
            }
            if (token.type === 'keyword') {
                // Handle keywords with trailing colon (e.g., 'public:', 'private:')
                const keyword = token.text.replace(/:$/, '');
                const colon = token.text.endsWith(':') ? ':' : '';
                return `<span class="hl-keyword">${keyword}</span>${colon}`;
            }
            if (token.type === 'type') {
                return `<span class="hl-type">${token.text}</span>`;
            }
            if (token.type === 'namespace') {
                return `<span class="hl-namespace">${token.text}</span>`;
            }
            if (token.type === 'number') {
                return `<span class="hl-number">${token.text}</span>`;
            }
            return escapeHtml(token.text);
        }).join('');
    }).join('\n');
}

function highlightAngleContent(content) {
    if (!content) return '';
    
    const types = [
        'Entity', 'Component', 'System', 'World', 'Renderer',
        'Shader', 'Mesh', 'Texture', 'Camera', 'Material',
        'Transform', 'Vec2', 'Vec3', 'Matrix4x4', 'Quaternion',
        'RigidBody', 'Collider', 'AudioSource', 'AudioBuffer',
        'GameEngine', 'std', 'string', 'vector', 'unique_ptr',
        'unordered_map', 'function', 'Mat4', 'Rect', 'Color',
        'IAssetLoader', 'TextureLoader', 'Asset', 'RingBuffer', 'ObjectPool',
        'GLFWwindow', 'Window', 'InputManager', 'Game', 'Scene',
        'memory', 'functional', 'string_view', 'optional', 'variant',
        'T', 'T1', 'T2', 'U', 'V', 'K', 'V1', 'V2'
    ];
    
    const keywords = ['class', 'typename', 'const', 'typename'];
    
    // Split by spaces and commas
    const parts = content.split(/([\s,]+)/);
    
    return parts.map(part => {
        if (/^[\s,]+$/.test(part)) return part;
        if (types.includes(part)) return `<span class="hl-type">${part}</span>`;
        if (keywords.includes(part)) return `<span class="hl-keyword">${part}</span>`;
        if (part.includes('::')) return `<span class="hl-namespace">${part}</span>`;
        return part;
    }).join('');
}

function tokenizeLine(line) {
    const tokens = [];
    
    // Keywords (including with colon suffix for access specifiers)
    const keywords = [
        'class', 'struct', 'enum', 'namespace', 'using', 'typedef',
        'public', 'private', 'protected', 'virtual', 'override', 'final',
        'public:', 'private:', 'protected:', 'override:',
        'const', 'static', 'inline', 'explicit', 'constexpr', 'default', 'delete',
        'template', 'typename', 'auto', 'nullptr', 'void',
        'int', 'float', 'double', 'bool', 'char', 'uint32_t', 'size_t',
        'return', 'if', 'else', 'for', 'while', 'do', 'switch',
        'case', 'break', 'continue', 'new', 'delete', 'this', 'true', 'false',
        'unsigned', 'long', 'short', 'signed', 'volatile', 'mutable', 'friend',
        'operator', 'sizeof', 'throw', 'try', 'catch'
    ];
    
    const types = [
        'Entity', 'Component', 'System', 'World', 'Renderer',
        'Shader', 'Mesh', 'Texture', 'Camera', 'Material',
        'Transform', 'Vec2', 'Vec3', 'Matrix4x4', 'Quaternion',
        'RigidBody', 'Collider', 'AudioSource', 'AudioBuffer',
        'GameEngine', 'std', 'string', 'vector', 'unique_ptr',
        'unordered_map', 'function', 'Mat4', 'Rect', 'Color',
        'IAssetLoader', 'TextureLoader', 'Asset', 'RingBuffer', 'ObjectPool',
        'GLFWwindow', 'Window', 'InputManager', 'Game', 'Scene',
        'memory', 'functional', 'string_view', 'optional', 'variant',
        'T', 'T1', 'T2', 'U', 'V', 'K', 'V1', 'V2'
    ];
    
    let i = 0;
    
    while (i < line.length) {
        // Comment
        if (line.slice(i, i + 2) === '//') {
            tokens.push({ type: 'comment', text: line.slice(i) });
            break;
        }
        
        // Angle brackets (templates)
        if (line[i] === '<') {
            let j = i + 1;
            let depth = 1;
            while (j < line.length && depth > 0) {
                if (line[j] === '<') depth++;
                if (line[j] === '>') depth--;
                j++;
            }
            tokens.push({ type: 'angle', text: line.slice(i, j) });
            i = j;
            continue;
        }
        
        // String (filenames)
        if (line[i] === '"') {
            let j = i + 1;
            while (j < line.length && line[j] !== '"') j++;
            tokens.push({ type: 'filename', text: line.slice(i, j + 1) });
            i = j + 1;
            continue;
        }
        
        // Preprocessor
        if (line[i] === '#' && (i === 0 || line[i-1] === '\n' || line[i-1] === '\r')) {
            let j = i + 1;
            while (j < line.length && /[a-z]/.test(line[j])) j++;
            tokens.push({ type: 'preprocessor', text: line.slice(i, j) });
            i = j;
            continue;
        }
        
        // Number
        if (/\d/.test(line[i])) {
            let j = i;
            while (j < line.length && /[\d.]/.test(line[j])) j++;
            tokens.push({ type: 'number', text: line.slice(i, j) });
            i = j;
            continue;
        }
        
        // Word (keyword, type, or identifier)
        if (/[a-zA-Z_]/.test(line[i])) {
            let j = i;
            // Include colons for keywords like 'public:', 'private:'
            while (j < line.length && /[a-zA-Z0-9_:]/.test(line[j])) j++;
            const word = line.slice(i, j);
            
            if (keywords.includes(word)) {
                tokens.push({ type: 'keyword', text: word });
            } else if (types.includes(word)) {
                tokens.push({ type: 'type', text: word });
            } else if (word.startsWith('std::') || word.includes('::')) {
                tokens.push({ type: 'namespace', text: word });
            } else {
                tokens.push({ type: 'text', text: word });
            }
            i = j;
            continue;
        }
        
        // Other characters
        tokens.push({ type: 'text', text: line[i] });
        i++;
    }
    
    return tokens;
}

/**
 * Animations and interactions
 */
function initAnimations() {
    const featureCards = document.querySelectorAll('.feature-card, .component-card, .shape-card, .concept-card');
    
    const cardObserver = new IntersectionObserver((entries) => {
        entries.forEach((entry, index) => {
            if (entry.isIntersecting) {
                entry.target.style.opacity = '0';
                entry.target.style.transform = 'translateY(20px)';
                
                setTimeout(() => {
                    entry.target.style.transition = 'opacity 0.5s ease, transform 0.5s ease';
                    entry.target.style.opacity = '1';
                    entry.target.style.transform = 'translateY(0)';
                }, index * 100);
                
                cardObserver.unobserve(entry.target);
            }
        });
    }, { threshold: 0.1 });
    
    featureCards.forEach(card => {
        cardObserver.observe(card);
    });
    
    const pipelineStages = document.querySelectorAll('.pipeline-stage');
    pipelineStages.forEach((stage, index) => {
        stage.style.opacity = '0';
        stage.style.transform = 'scale(0.9)';
        
        setTimeout(() => {
            stage.style.transition = 'opacity 0.4s ease, transform 0.4s ease';
            stage.style.opacity = '1';
            stage.style.transform = 'scale(1)';
        }, 200 + index * 150);
    });
}

/**
 * Search functionality
 */
function initSearch() {
    const searchInput = document.createElement('input');
    searchInput.type = 'text';
    searchInput.placeholder = 'Search documentation...';
    searchInput.className = 'search-input';
    
    const main = document.querySelector('.content');
    main.insertBefore(searchInput, main.firstChild);
    
    searchInput.addEventListener('input', (e) => {
        const query = e.target.value.toLowerCase();
        const sections = document.querySelectorAll('.doc-section');
        
        sections.forEach(section => {
            const content = section.textContent.toLowerCase();
            section.style.display = content.includes(query) || query === '' ? 'block' : 'none';
        });
    });
}

/**
 * Progress indicator
 */
function initProgressIndicator() {
    const progress = document.createElement('div');
    progress.className = 'reading-progress';
    document.body.appendChild(progress);
    
    window.addEventListener('scroll', () => {
        const scrollTop = window.scrollY;
        const docHeight = document.documentElement.scrollHeight - window.innerHeight;
        const progressPercent = (scrollTop / docHeight) * 100;
        progress.style.width = `${progressPercent}%`;
    });
    
    const printButton = document.createElement('button');
    printButton.textContent = 'Print / Export PDF';
    printButton.className = 'print-button';
    printButton.addEventListener('click', () => {
        window.print();
    });
    document.body.appendChild(printButton);
}
