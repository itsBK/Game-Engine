const { useState } = React;

const sections = [
  { id: "overview", label: "Overview" },
  { id: "requirements", label: "Requirements" },
  { id: "architecture", label: "Architecture" },
  { id: "uml", label: "UML Diagram" },
  { id: "roadmap", label: "Roadmap" },
  { id: "platform", label: "Platform Strategy" },
];

const modules = [
  {
    id: "core", name: "Core", color: "#00d4ff", bg: "#00d4ff18", border: "#00d4ff40", priority: "P0",
    classes: ["Engine", "Application", "Timer", "Logger", "EventBus", "FileSystem"],
    desc: "Bootstrap, lifecycle, event dispatch, platform abstraction",
  },
  {
    id: "math", name: "Math", color: "#a78bfa", bg: "#a78bfa18", border: "#a78bfa40", priority: "P0",
    classes: ["Vec2", "Vec3", "Vec4", "Mat3", "Mat4", "Quat", "AABB", "Frustum", "Ray", "MathUtils"],
    desc: "Linear algebra, geometric primitives, interpolation utilities",
  },
  {
    id: "renderer", name: "Renderer", color: "#f59e0b", bg: "#f59e0b18", border: "#f59e0b40", priority: "P0",
    classes: ["RenderContext", "Shader", "Texture", "Mesh", "Camera", "Material", "RenderPass", "FrameBuffer", "BatchRenderer", "Renderer2D", "Renderer3D"],
    desc: "OpenGL/ES abstraction, 2D sprites/batching, 3D meshes, shader pipeline",
  },
  {
    id: "physics", name: "Physics", color: "#34d399", bg: "#34d39918", border: "#34d39940", priority: "P1",
    classes: ["PhysicsWorld", "RigidBody", "Collider", "CollisionDetector", "BroadPhase", "NarrowPhase", "Manifold", "Constraint", "Solver"],
    desc: "Rigid body dynamics, constraint solver, broadphase/narrowphase detection",
  },
  {
    id: "collision", name: "Collision", color: "#fb7185", bg: "#fb718518", border: "#fb718540", priority: "P0",
    classes: ["BVH", "Octree", "QuadTree", "GJK", "EPA", "SAT", "RaycastQuery", "OverlapQuery"],
    desc: "Spatial partitioning, GJK/EPA/SAT algorithms, raycasting, queries",
  },
  {
    id: "animation", name: "Animation", color: "#fb923c", bg: "#fb923c18", border: "#fb923c40", priority: "P1",
    classes: ["Animator", "AnimationClip", "Skeleton", "Bone", "Skinning", "Tweener", "Timeline", "BlendTree"],
    desc: "Skeletal animation, blend trees, tweening, timeline system",
  },
  {
    id: "scene", name: "Scene", color: "#38bdf8", bg: "#38bdf818", border: "#38bdf840", priority: "P0",
    classes: ["Scene", "SceneNode", "Transform", "Component", "Entity", "ComponentRegistry"],
    desc: "Scene graph, entity-component system, transform hierarchy",
  },
  {
    id: "network", name: "Networking", color: "#e879f9", bg: "#e879f918", border: "#e879f940", priority: "P2",
    classes: ["NetworkManager", "Socket", "Packet", "Serializer", "ReplicationSystem", "LockstepManager"],
    desc: "UDP/TCP sockets, packet serialization, basic state replication",
  },
  {
    id: "assets", name: "Assets", color: "#fbbf24", bg: "#fbbf2418", border: "#fbbf2440", priority: "P1",
    classes: ["AssetManager", "AssetLoader", "ResourceCache", "MeshLoader", "TextureLoader", "AudioLoader"],
    desc: "Async loading, reference counting, cache eviction, format parsers",
  },
  {
    id: "audio", name: "Audio", color: "#4ade80", bg: "#4ade8018", border: "#4ade8040", priority: "P2",
    classes: ["AudioSystem", "AudioSource", "AudioClip", "AudioListener", "Mixer"],
    desc: "Positional audio, mixing, OpenAL/miniaudio backend",
  },
];

const requirements = [
  { id: "FR-01", type: "Functional", priority: "MUST", title: "2D Rendering", desc: "Render sprites, tilemaps, and primitives via batched draw calls using OpenGL 3.3 / OpenGL ES 3.0" },
  { id: "FR-02", type: "Functional", priority: "MUST", title: "3D Rendering", desc: "Forward rendering of 3D meshes with PBR-lite materials, directional/point/spot lights, and shadow maps" },
  { id: "FR-03", type: "Functional", priority: "MUST", title: "Fixed + Custom Pipelines", desc: "Provide a built-in fixed render pipeline; allow user-defined RenderPass chain with custom shaders" },
  { id: "FR-04", type: "Functional", priority: "MUST", title: "Math Library", desc: "SIMD-friendly Vec2/3/4, Mat3/4, Quaternion; geometric primitives AABB, Ray, Frustum; common interpolation" },
  { id: "FR-05", type: "Functional", priority: "MUST", title: "Collision Detection", desc: "BVH / QuadTree broadphase; GJK+EPA & SAT narrowphase; raycasting; overlap/trigger queries" },
  { id: "FR-06", type: "Functional", priority: "MUST", title: "Scene Graph + ECS", desc: "Hierarchical scene nodes, transform propagation, lightweight entity-component system" },
  { id: "FR-07", type: "Functional", priority: "SHOULD", title: "Physics Simulation", desc: "Rigid body dynamics, AABB/Sphere/Capsule/Box colliders, impulse solver, sleeping islands" },
  { id: "FR-08", type: "Functional", priority: "SHOULD", title: "Animation System", desc: "Skeletal animation with GPU skinning, blend trees, tweener for properties, clip timeline" },
  { id: "FR-09", type: "Functional", priority: "SHOULD", title: "Asset Pipeline", desc: "Async asset loading, reference-counted cache, loaders for OBJ/glTF, PNG/KTX, WAV/OGG" },
  { id: "FR-10", type: "Functional", priority: "COULD", title: "Simple Networking", desc: "UDP socket wrapper, reliable packet layer, basic state-replication helper for up to 8 peers" },
  { id: "FR-11", type: "Functional", priority: "COULD", title: "Audio System", desc: "Positional 3D audio, channel mixing, OpenAL or miniaudio backend" },
  { id: "NFR-01", type: "Non-Functional", priority: "MUST", title: "Cross-Platform", desc: "Single CMake project targets Windows/Linux/macOS (OpenGL 3.3) and Android NDK (OpenGL ES 3.0)" },
  { id: "NFR-02", type: "Non-Functional", priority: "MUST", title: "C++17 Standard", desc: "Library header + static/shared lib, no runtime exceptions in hot paths, zero mandatory RTTI" },
  { id: "NFR-03", type: "Non-Functional", priority: "MUST", title: "Performance", desc: "60+ FPS on mid-tier mobile (Adreno 640); <2ms physics step per frame; draw call batching" },
  { id: "NFR-04", type: "Non-Functional", priority: "SHOULD", title: "Minimal Dependencies", desc: "Only: GLFW (desktop), glad, glm (replaceable), stb_image, miniaudio, asio (networking)" },
];

const roadmapPhases = [
  {
    phase: "Phase 0", title: "Foundation", duration: "Weeks 1–3", color: "#00d4ff",
    items: [
      "CMake project structure (PC + Android NDK)",
      "Platform abstraction layer (Window, Input, FileSystem)",
      "Core: Engine loop, Timer, Logger, EventBus",
      "Math library: Vec2/3/4, Mat3/4, Quat, AABB, Ray",
      "OpenGL context creation (GLFW + EGL for Android)",
    ],
  },
  {
    phase: "Phase 1", title: "Rendering Core", duration: "Weeks 4–7", color: "#f59e0b",
    items: [
      "Shader, Texture, Mesh, FrameBuffer abstractions",
      "2D Batch Renderer (sprites, quads, text glyphs)",
      "Camera (ortho + perspective), Frustum culling",
      "Fixed pipeline: Z-prepass → Geometry → Post",
      "Custom RenderPass chain API",
      "OpenGL 3.3 ↔ OpenGL ES 3.0 compile-time switch",
    ],
  },
  {
    phase: "Phase 2", title: "Scene + Collision", duration: "Weeks 8–10", color: "#34d399",
    items: [
      "Scene graph, SceneNode, Transform hierarchy",
      "Entity-Component System (registry + component pools)",
      "BVH / QuadTree broadphase",
      "GJK + EPA, SAT narrowphase solvers",
      "Raycast & overlap query API",
      "Debug draw overlay for shapes",
    ],
  },
  {
    phase: "Phase 3", title: "Physics + 3D", duration: "Weeks 11–14", color: "#a78bfa",
    items: [
      "RigidBody, collider shapes (AABB/Sphere/Capsule/Box)",
      "Impulse-based constraint solver",
      "Sleeping island optimization",
      "3D forward renderer: PBR-lite, point/dir/spot lights",
      "Shadow mapping (directional CSM)",
      "Asset Manager + loaders (OBJ, glTF, PNG/KTX)",
    ],
  },
  {
    phase: "Phase 4", title: "Animation + Audio", duration: "Weeks 15–17", color: "#fb923c",
    items: [
      "Skeleton + Bone hierarchy, AnimationClip",
      "GPU skinning (vertex shader)",
      "BlendTree (1D / 2D parameter space)",
      "Property tweener + Timeline",
      "Audio system: positional 3D, mixing (miniaudio)",
    ],
  },
  {
    phase: "Phase 5", title: "Networking + Polish", duration: "Weeks 18–20", color: "#e879f9",
    items: [
      "UDP Socket wrapper (asio / BSD sockets / Android)",
      "Reliable ordered packet layer",
      "Basic ReplicationSystem (state snapshots)",
      "API documentation + usage examples",
      "Android NDK integration guide + sample APK",
      "Performance profiling pass",
    ],
  },
];

function App() {
  const [activeSection, setActiveSection] = useState("overview");
  const [activeModule, setActiveModule] = useState(null);
  const [expandedReq, setExpandedReq] = useState(null);

  const selectedModule = modules.find((m) => m.id === activeModule);

  return (
    <div style={{ minHeight: "100vh", background: "#080c14", color: "#e2e8f0", fontFamily: "'JetBrains Mono', 'Fira Code', monospace", fontSize: "13px" }}>
      <style>{`
        @import url('https://fonts.googleapis.com/css2?family=JetBrains+Mono:wght@300;400;500;700&family=Orbitron:wght@700;900&display=swap');
        * { box-sizing: border-box; margin: 0; padding: 0; }
        ::-webkit-scrollbar { width: 4px; background: #0d1220; }
        ::-webkit-scrollbar-thumb { background: #1e3a5f; border-radius: 2px; }
        .nav-btn { transition: all 0.2s; }
        .nav-btn:hover { color: #00d4ff !important; }
        .module-card { transition: all 0.2s; cursor: pointer; }
        .module-card:hover { transform: translateY(-2px); box-shadow: 0 4px 20px #00000060; }
        .req-row { transition: background 0.15s; cursor: pointer; }
        .req-row:hover { background: #ffffff08 !important; }
        @keyframes pulse { 0%,100%{opacity:1} 50%{opacity:0.5} }
        .live-dot { animation: pulse 2s infinite; }
        @keyframes fadeIn { from{opacity:0;transform:translateY(8px)} to{opacity:1;transform:translateY(0)} }
        .section-content { animation: fadeIn 0.3s ease; }
      `}</style>

      {/* Header */}
      <div style={{ borderBottom: "1px solid #1a2d4a", padding: "16px 32px", display: "flex", alignItems: "center", gap: "16px", background: "linear-gradient(90deg,#0d1220,#091828)", position: "sticky", top: 0, zIndex: 100 }}>
        <div>
          <div style={{ fontFamily: "'Orbitron',sans-serif", fontSize: "17px", fontWeight: 900, color: "#00d4ff", letterSpacing: "0.1em" }}>◈ NOVA ENGINE</div>
          <div style={{ color: "#4a6a8a", fontSize: "10px", letterSpacing: "0.15em" }}>C++ · OpenGL · Android NDK · PLANNING v1.0</div>
        </div>
        <div style={{ flex: 1 }} />
        <div style={{ display: "flex", gap: "6px", alignItems: "center" }}>
          <span className="live-dot" style={{ width: 8, height: 8, borderRadius: "50%", background: "#34d399", display: "inline-block" }} />
          <span style={{ color: "#34d399", fontSize: "10px", letterSpacing: "0.1em" }}>PLANNING MODE</span>
        </div>
      </div>

      {/* Nav */}
      <div style={{ display: "flex", padding: "0 32px", borderBottom: "1px solid #1a2d4a", background: "#0a1018", overflowX: "auto" }}>
        {sections.map((s) => (
          <button key={s.id} className="nav-btn" onClick={() => setActiveSection(s.id)} style={{ background: "none", border: "none", borderBottom: activeSection === s.id ? "2px solid #00d4ff" : "2px solid transparent", color: activeSection === s.id ? "#00d4ff" : "#5a7a9a", padding: "12px 20px", cursor: "pointer", fontSize: "11px", letterSpacing: "0.1em", fontFamily: "inherit", whiteSpace: "nowrap" }}>
            {s.label.toUpperCase()}
          </button>
        ))}
      </div>

      {/* Content */}
      <div style={{ padding: "32px", maxWidth: "1100px", margin: "0 auto" }}>

        {/* OVERVIEW */}
        {activeSection === "overview" && (
          <div className="section-content">
            <h2 style={{ fontFamily: "'Orbitron',sans-serif", color: "#00d4ff", marginBottom: 8, fontSize: 18 }}>Engine Overview</h2>
            <p style={{ color: "#7a9aba", lineHeight: 1.8, marginBottom: 28, maxWidth: 700 }}>
              <b style={{ color: "#00d4ff" }}>Nova Engine</b> is a lightweight, modular C++17 game framework targeting PC (OpenGL 3.3) and Android NDK (OpenGL ES 3.0). Designed with requirement engineering discipline — only components that solve real game development problems are included.
            </p>
            <div style={{ display: "grid", gridTemplateColumns: "repeat(auto-fill,minmax(240px,1fr))", gap: 12, marginBottom: 32 }}>
              {[
                { label: "Language", value: "C++17", icon: "⚙" },
                { label: "Desktop Renderer", value: "OpenGL 3.3 Core", icon: "🖥" },
                { label: "Mobile Renderer", value: "OpenGL ES 3.0 (NDK)", icon: "📱" },
                { label: "Build System", value: "CMake 3.21+", icon: "🔧" },
                { label: "Architecture", value: "ECS + Scene Graph", icon: "🏗" },
                { label: "Library Type", value: "Static + Shared (.so/.dll)", icon: "📦" },
              ].map((item) => (
                <div key={item.label} style={{ background: "#0d1828", border: "1px solid #1a2d4a", borderRadius: 8, padding: "16px", display: "flex", gap: 12, alignItems: "center" }}>
                  <span style={{ fontSize: 20 }}>{item.icon}</span>
                  <div>
                    <div style={{ color: "#4a6a8a", fontSize: 10, letterSpacing: "0.1em", marginBottom: 2 }}>{item.label.toUpperCase()}</div>
                    <div style={{ color: "#e2e8f0", fontWeight: 500 }}>{item.value}</div>
                  </div>
                </div>
              ))}
            </div>
            <h3 style={{ color: "#a78bfa", marginBottom: 16, fontSize: 13, letterSpacing: "0.1em" }}>MODULES ({modules.length} total)</h3>
            <div style={{ display: "grid", gridTemplateColumns: "repeat(auto-fill,minmax(200px,1fr))", gap: 10 }}>
              {modules.map((m) => (
                <div key={m.id} className="module-card" onClick={() => { setActiveModule(m.id); setActiveSection("architecture"); }} style={{ background: m.bg, border: `1px solid ${m.border}`, borderRadius: 8, padding: "14px 16px" }}>
                  <div style={{ display: "flex", justifyContent: "space-between", alignItems: "center", marginBottom: 6 }}>
                    <span style={{ color: m.color, fontWeight: 700, fontSize: 12 }}>{m.name}</span>
                    <span style={{ fontSize: 9, padding: "2px 6px", borderRadius: 4, background: m.priority === "P0" ? "#ff444420" : m.priority === "P1" ? "#f59e0b20" : "#a78bfa20", color: m.priority === "P0" ? "#ff6666" : m.priority === "P1" ? "#f59e0b" : "#a78bfa", border: `1px solid ${m.priority === "P0" ? "#ff444440" : m.priority === "P1" ? "#f59e0b40" : "#a78bfa40"}` }}>{m.priority}</span>
                  </div>
                  <div style={{ color: "#5a7a9a", fontSize: 11, lineHeight: 1.5 }}>{m.desc}</div>
                  <div style={{ marginTop: 8, color: "#3a5a7a", fontSize: 10 }}>{m.classes.length} classes</div>
                </div>
              ))}
            </div>
          </div>
        )}

        {/* REQUIREMENTS */}
        {activeSection === "requirements" && (
          <div className="section-content">
            <h2 style={{ fontFamily: "'Orbitron',sans-serif", color: "#00d4ff", marginBottom: 8, fontSize: 18 }}>Requirements Engineering</h2>
            <p style={{ color: "#7a9aba", marginBottom: 24, lineHeight: 1.7, maxWidth: 680 }}>Applying MoSCoW prioritization. Only <b style={{ color: "#e2e8f0" }}>MUST</b> and <b style={{ color: "#e2e8f0" }}>SHOULD</b> items are in scope for v1.0. COULD items are future milestones.</p>
            <div style={{ display: "flex", gap: 12, marginBottom: 24, flexWrap: "wrap" }}>
              {[
                { label: "MUST", count: requirements.filter((r) => r.priority === "MUST").length, color: "#00d4ff" },
                { label: "SHOULD", count: requirements.filter((r) => r.priority === "SHOULD").length, color: "#a78bfa" },
                { label: "COULD", count: requirements.filter((r) => r.priority === "COULD").length, color: "#4a6a8a" },
                { label: "Functional", count: requirements.filter((r) => r.type === "Functional").length, color: "#34d399" },
                { label: "Non-Functional", count: requirements.filter((r) => r.type === "Non-Functional").length, color: "#fb923c" },
              ].map((s) => (
                <div key={s.label} style={{ background: "#0d1828", border: "1px solid #1a2d4a", borderRadius: 6, padding: "8px 14px", display: "flex", gap: 8, alignItems: "center" }}>
                  <span style={{ color: s.color, fontWeight: 700, fontSize: 16 }}>{s.count}</span>
                  <span style={{ color: "#5a7a9a", fontSize: 11 }}>{s.label}</span>
                </div>
              ))}
            </div>
            <div style={{ border: "1px solid #1a2d4a", borderRadius: 8, overflow: "hidden" }}>
              <div style={{ display: "grid", gridTemplateColumns: "80px 120px 80px 1fr", padding: "10px 16px", background: "#0a1220", color: "#4a6a8a", fontSize: 10, letterSpacing: "0.1em", borderBottom: "1px solid #1a2d4a" }}>
                <span>ID</span><span>TYPE</span><span>PRIORITY</span><span>REQUIREMENT</span>
              </div>
              {requirements.map((r) => (
                <div key={r.id}>
                  <div className="req-row" onClick={() => setExpandedReq(expandedReq === r.id ? null : r.id)} style={{ display: "grid", gridTemplateColumns: "80px 120px 80px 1fr", padding: "12px 16px", borderBottom: "1px solid #0f1e30", background: expandedReq === r.id ? "#0d1828" : "transparent" }}>
                    <span style={{ color: "#4a6a8a", fontSize: 11 }}>{r.id}</span>
                    <span style={{ color: r.type === "Functional" ? "#34d399" : "#fb923c", fontSize: 11 }}>{r.type}</span>
                    <span style={{ fontSize: 10, padding: "2px 6px", borderRadius: 4, display: "inline-block", height: "fit-content", background: r.priority === "MUST" ? "#00d4ff15" : r.priority === "SHOULD" ? "#a78bfa15" : "#4a6a8a15", color: r.priority === "MUST" ? "#00d4ff" : r.priority === "SHOULD" ? "#a78bfa" : "#4a6a8a" }}>{r.priority}</span>
                    <span style={{ color: "#c2d8f0" }}>{r.title}</span>
                  </div>
                  {expandedReq === r.id && (
                    <div style={{ padding: "12px 16px 12px 80px", background: "#0a1220", borderBottom: "1px solid #0f1e30", color: "#7a9aba", lineHeight: 1.7 }}>{r.desc}</div>
                  )}
                </div>
              ))}
            </div>
          </div>
        )}

        {/* ARCHITECTURE */}
        {activeSection === "architecture" && (
          <div className="section-content">
            <h2 style={{ fontFamily: "'Orbitron',sans-serif", color: "#00d4ff", marginBottom: 8, fontSize: 18 }}>Module Architecture</h2>
            <p style={{ color: "#7a9aba", marginBottom: 24, lineHeight: 1.7, maxWidth: 680 }}>Click a module to inspect its class inventory. Each module is a standalone compilation unit with a public header API surface and an internal implementation layer.</p>
            <div style={{ display: "flex", gap: 16 }}>
              <div style={{ flex: "0 0 220px" }}>
                {modules.map((m) => (
                  <div key={m.id} className="module-card" onClick={() => setActiveModule(activeModule === m.id ? null : m.id)} style={{ background: activeModule === m.id ? m.bg : "#0d1828", border: `1px solid ${activeModule === m.id ? m.color : "#1a2d4a"}`, borderRadius: 6, padding: "10px 14px", marginBottom: 6, display: "flex", justifyContent: "space-between", alignItems: "center" }}>
                    <span style={{ color: activeModule === m.id ? m.color : "#c2d8f0", fontSize: 12, fontWeight: activeModule === m.id ? 700 : 400 }}>{m.name}</span>
                    <span style={{ color: "#4a6a8a", fontSize: 10 }}>{m.classes.length}</span>
                  </div>
                ))}
              </div>
              <div style={{ flex: 1 }}>
                {selectedModule ? (
                  <div>
                    <div style={{ background: selectedModule.bg, border: `1px solid ${selectedModule.border}`, borderRadius: 8, padding: "20px 24px", marginBottom: 16 }}>
                      <div style={{ display: "flex", justifyContent: "space-between", alignItems: "flex-start", marginBottom: 12 }}>
                        <div>
                          <div style={{ fontFamily: "'Orbitron',sans-serif", color: selectedModule.color, fontSize: 16, marginBottom: 4 }}>{selectedModule.name} Module</div>
                          <div style={{ color: "#7a9aba", lineHeight: 1.7 }}>{selectedModule.desc}</div>
                        </div>
                        <span style={{ fontSize: 10, padding: "4px 10px", borderRadius: 6, background: "#00000030", color: selectedModule.color, border: `1px solid ${selectedModule.border}`, flexShrink: 0, marginLeft: 16 }}>{selectedModule.priority}</span>
                      </div>
                    </div>
                    <h4 style={{ color: "#4a6a8a", fontSize: 10, letterSpacing: "0.1em", marginBottom: 12 }}>CLASS INVENTORY</h4>
                    <div style={{ display: "grid", gridTemplateColumns: "repeat(auto-fill,minmax(150px,1fr))", gap: 8 }}>
                      {selectedModule.classes.map((cls) => (
                        <div key={cls} style={{ background: "#0d1828", border: "1px solid #1a2d4a", borderRadius: 6, padding: "10px 12px" }}>
                          <div style={{ color: selectedModule.color, fontSize: 11, fontWeight: 500, marginBottom: 2 }}>{cls}</div>
                          <div style={{ color: "#3a5a7a", fontSize: 10 }}>class</div>
                        </div>
                      ))}
                    </div>
                  </div>
                ) : (
                  <div style={{ height: 300, display: "flex", alignItems: "center", justifyContent: "center", border: "1px dashed #1a2d4a", borderRadius: 8, color: "#3a5a7a" }}>← Select a module to inspect</div>
                )}
              </div>
            </div>
          </div>
        )}

        {/* UML */}
        {activeSection === "uml" && (
          <div className="section-content">
            <h2 style={{ fontFamily: "'Orbitron',sans-serif", color: "#00d4ff", marginBottom: 8, fontSize: 18 }}>UML Component Diagram</h2>
            <p style={{ color: "#7a9aba", marginBottom: 24, lineHeight: 1.7 }}>Dependency graph showing all major components. Arrows indicate "depends on / uses" relationships. Engine is the root aggregator.</p>
            <div style={{ display: "flex", gap: 12, marginBottom: 20, flexWrap: "wrap" }}>
              {[
                { label: "Core / Scene", color: "#38bdf8" }, { label: "Renderer", color: "#f59e0b" },
                { label: "Physics", color: "#34d399" }, { label: "Collision", color: "#fb7185" },
                { label: "Assets", color: "#fbbf24" }, { label: "Audio", color: "#4ade80" },
                { label: "Network", color: "#e879f9" }, { label: "Math (shared)", color: "#a78bfa" },
              ].map((l) => (
                <div key={l.label} style={{ display: "flex", alignItems: "center", gap: 6 }}>
                  <div style={{ width: 10, height: 10, borderRadius: 2, background: l.color }} />
                  <span style={{ color: "#5a7a9a", fontSize: 10 }}>{l.label}</span>
                </div>
              ))}
            </div>
            <div style={{ overflowX: "auto", overflowY: "auto", maxHeight: 640, border: "1px solid #1a2d4a", borderRadius: 8, background: "#080c14", padding: 16 }}>
              <svg width="800" height="640" viewBox="0 0 800 640">
                <defs>
                  <marker id="arrow" markerWidth="8" markerHeight="8" refX="7" refY="3" orient="auto">
                    <path d="M0,0 L0,6 L8,3 z" fill="#2a4a6a" />
                  </marker>
                </defs>
                {/* Math */}
                <rect x="340" y="580" width="120" height="44" rx="6" fill="#a78bfa18" stroke="#a78bfa60" strokeWidth="1.5" />
                <text x="400" y="597" textAnchor="middle" fill="#a78bfa" fontSize="11" fontFamily="JetBrains Mono,monospace" fontWeight="700">Math</text>
                <text x="400" y="613" textAnchor="middle" fill="#6a5a9a" fontSize="9" fontFamily="JetBrains Mono,monospace">Vec·Mat·Quat·AABB</text>
                {/* Engine */}
                <rect x="310" y="10" width="180" height="44" rx="6" fill="#00d4ff18" stroke="#00d4ff60" strokeWidth="2" />
                <text x="400" y="27" textAnchor="middle" fill="#00d4ff" fontSize="12" fontFamily="JetBrains Mono,monospace" fontWeight="700">Engine</text>
                <text x="400" y="44" textAnchor="middle" fill="#3a7a9a" fontSize="9" fontFamily="JetBrains Mono,monospace">Root Aggregator · Lifecycle</text>
                {/* Scene */}
                <rect x="30" y="120" width="140" height="44" rx="6" fill="#38bdf818" stroke="#38bdf840" strokeWidth="1.5" />
                <text x="100" y="137" textAnchor="middle" fill="#38bdf8" fontSize="11" fontFamily="JetBrains Mono,monospace" fontWeight="700">Scene</text>
                <text x="100" y="153" textAnchor="middle" fill="#3a7a9a" fontSize="9" fontFamily="JetBrains Mono,monospace">Graph · ECS · Entities</text>
                {/* SceneNode */}
                <rect x="30" y="240" width="130" height="36" rx="5" fill="#38bdf818" stroke="#38bdf830" />
                <text x="95" y="263" textAnchor="middle" fill="#38bdf8" fontSize="10" fontFamily="JetBrains Mono,monospace">SceneNode</text>
                {/* Transform */}
                <rect x="30" y="350" width="120" height="36" rx="5" fill="#38bdf818" stroke="#38bdf830" />
                <text x="90" y="373" textAnchor="middle" fill="#38bdf8" fontSize="10" fontFamily="JetBrains Mono,monospace">Transform</text>
                {/* Entity */}
                <rect x="175" y="240" width="120" height="36" rx="5" fill="#38bdf818" stroke="#38bdf830" />
                <text x="235" y="263" textAnchor="middle" fill="#38bdf8" fontSize="10" fontFamily="JetBrains Mono,monospace">Entity</text>
                {/* Component */}
                <rect x="175" y="350" width="120" height="36" rx="5" fill="#38bdf818" stroke="#38bdf830" />
                <text x="235" y="373" textAnchor="middle" fill="#38bdf8" fontSize="10" fontFamily="JetBrains Mono,monospace">Component</text>
                {/* Renderer */}
                <rect x="310" y="120" width="160" height="44" rx="6" fill="#f59e0b18" stroke="#f59e0b40" strokeWidth="1.5" />
                <text x="390" y="137" textAnchor="middle" fill="#f59e0b" fontSize="11" fontFamily="JetBrains Mono,monospace" fontWeight="700">Renderer</text>
                <text x="390" y="153" textAnchor="middle" fill="#7a6a3a" fontSize="9" fontFamily="JetBrains Mono,monospace">2D/3D · Fixed/Custom</text>
                {/* RenderPass */}
                <rect x="480" y="240" width="130" height="36" rx="5" fill="#f59e0b18" stroke="#f59e0b30" />
                <text x="545" y="263" textAnchor="middle" fill="#f59e0b" fontSize="10" fontFamily="JetBrains Mono,monospace">RenderPass</text>
                {/* Camera */}
                <rect x="320" y="240" width="120" height="36" rx="5" fill="#f59e0b18" stroke="#f59e0b30" />
                <text x="380" y="263" textAnchor="middle" fill="#f59e0b" fontSize="10" fontFamily="JetBrains Mono,monospace">Camera</text>
                {/* Shader / Mesh / Texture */}
                <rect x="630" y="120" width="120" height="36" rx="5" fill="#f59e0b18" stroke="#f59e0b30" />
                <text x="690" y="143" textAnchor="middle" fill="#f59e0b" fontSize="10" fontFamily="JetBrains Mono,monospace">Shader</text>
                <rect x="630" y="170" width="120" height="36" rx="5" fill="#f59e0b18" stroke="#f59e0b30" />
                <text x="690" y="193" textAnchor="middle" fill="#f59e0b" fontSize="10" fontFamily="JetBrains Mono,monospace">Mesh</text>
                <rect x="630" y="220" width="120" height="36" rx="5" fill="#f59e0b18" stroke="#f59e0b30" />
                <text x="690" y="243" textAnchor="middle" fill="#f59e0b" fontSize="10" fontFamily="JetBrains Mono,monospace">Texture</text>
                {/* PhysicsWorld */}
                <rect x="310" y="400" width="150" height="44" rx="6" fill="#34d39918" stroke="#34d39940" strokeWidth="1.5" />
                <text x="385" y="417" textAnchor="middle" fill="#34d399" fontSize="11" fontFamily="JetBrains Mono,monospace" fontWeight="700">PhysicsWorld</text>
                <text x="385" y="433" textAnchor="middle" fill="#3a7a6a" fontSize="9" fontFamily="JetBrains Mono,monospace">RigidBody · Solver</text>
                {/* CollisionDetector */}
                <rect x="310" y="510" width="150" height="44" rx="6" fill="#fb718518" stroke="#fb718540" strokeWidth="1.5" />
                <text x="385" y="527" textAnchor="middle" fill="#fb7185" fontSize="10" fontFamily="JetBrains Mono,monospace" fontWeight="700">CollisionDetector</text>
                <text x="385" y="543" textAnchor="middle" fill="#7a3a4a" fontSize="9" fontFamily="JetBrains Mono,monospace">BVH · GJK · SAT</text>
                {/* BVH / GJK */}
                <rect x="475" y="510" width="80" height="36" rx="5" fill="#fb718518" stroke="#fb718530" />
                <text x="515" y="533" textAnchor="middle" fill="#fb7185" fontSize="9" fontFamily="JetBrains Mono,monospace">BVH</text>
                <rect x="565" y="510" width="90" height="36" rx="5" fill="#fb718518" stroke="#fb718530" />
                <text x="610" y="533" textAnchor="middle" fill="#fb7185" fontSize="9" fontFamily="JetBrains Mono,monospace">GJK/EPA</text>
                {/* AssetManager */}
                <rect x="30" y="400" width="140" height="44" rx="6" fill="#fbbf2418" stroke="#fbbf2440" strokeWidth="1.5" />
                <text x="100" y="417" textAnchor="middle" fill="#fbbf24" fontSize="11" fontFamily="JetBrains Mono,monospace" fontWeight="700">AssetManager</text>
                <text x="100" y="433" textAnchor="middle" fill="#7a6a3a" fontSize="9" fontFamily="JetBrains Mono,monospace">Cache · Loaders</text>
                {/* AudioSystem */}
                <rect x="30" y="510" width="140" height="44" rx="6" fill="#4ade8018" stroke="#4ade8040" strokeWidth="1.5" />
                <text x="100" y="527" textAnchor="middle" fill="#4ade80" fontSize="11" fontFamily="JetBrains Mono,monospace" fontWeight="700">AudioSystem</text>
                <text x="100" y="543" textAnchor="middle" fill="#3a7a5a" fontSize="9" fontFamily="JetBrains Mono,monospace">Positional · Mixing</text>
                {/* NetworkManager */}
                <rect x="175" y="120" width="130" height="44" rx="6" fill="#e879f918" stroke="#e879f940" strokeWidth="1.5" />
                <text x="240" y="137" textAnchor="middle" fill="#e879f9" fontSize="10" fontFamily="JetBrains Mono,monospace" fontWeight="700">NetworkManager</text>
                <text x="240" y="153" textAnchor="middle" fill="#7a3a9a" fontSize="9" fontFamily="JetBrains Mono,monospace">UDP · Replication</text>
                {/* Arrows */}
                <line x1="340" y1="54" x2="150" y2="120" stroke="#1a3a5a" strokeWidth="1" markerEnd="url(#arrow)" />
                <line x1="390" y1="54" x2="390" y2="120" stroke="#1a3a5a" strokeWidth="1" markerEnd="url(#arrow)" />
                <line x1="355" y1="54" x2="280" y2="120" stroke="#1a3a5a" strokeWidth="1" markerEnd="url(#arrow)" />
                <line x1="320" y1="50" x2="120" y2="400" stroke="#1a3a5a" strokeWidth="1" strokeDasharray="4,3" markerEnd="url(#arrow)" />
                <line x1="400" y1="54" x2="390" y2="400" stroke="#1a3a5a" strokeWidth="1" markerEnd="url(#arrow)" />
                <line x1="315" y1="48" x2="110" y2="510" stroke="#1a3a5a" strokeWidth="1" strokeDasharray="4,3" markerEnd="url(#arrow)" />
                <line x1="95" y1="164" x2="90" y2="240" stroke="#2a5a7a" strokeWidth="1" markerEnd="url(#arrow)" />
                <line x1="120" y1="164" x2="210" y2="240" stroke="#2a5a7a" strokeWidth="1" markerEnd="url(#arrow)" />
                <line x1="85" y1="276" x2="82" y2="350" stroke="#2a5a7a" strokeWidth="1" markerEnd="url(#arrow)" />
                <line x1="232" y1="276" x2="232" y2="350" stroke="#2a5a7a" strokeWidth="1" markerEnd="url(#arrow)" />
                <line x1="470" y1="150" x2="535" y2="240" stroke="#7a5a1a" strokeWidth="1" markerEnd="url(#arrow)" />
                <line x1="390" y1="164" x2="385" y2="240" stroke="#7a5a1a" strokeWidth="1" markerEnd="url(#arrow)" />
                <line x1="470" y1="138" x2="630" y2="138" stroke="#7a5a1a" strokeWidth="1" markerEnd="url(#arrow)" />
                <line x1="470" y1="148" x2="630" y2="185" stroke="#7a5a1a" strokeWidth="1" markerEnd="url(#arrow)" />
                <line x1="470" y1="155" x2="630" y2="232" stroke="#7a5a1a" strokeWidth="1" markerEnd="url(#arrow)" />
                <line x1="385" y1="444" x2="385" y2="510" stroke="#2a6a4a" strokeWidth="1" markerEnd="url(#arrow)" />
                <line x1="460" y1="532" x2="475" y2="532" stroke="#6a2a3a" strokeWidth="1" markerEnd="url(#arrow)" />
                <line x1="460" y1="537" x2="565" y2="537" stroke="#6a2a3a" strokeWidth="1" markerEnd="url(#arrow)" />
                <line x1="390" y1="580" x2="385" y2="560" stroke="#5a4a9a" strokeWidth="1" strokeDasharray="3,3" markerEnd="url(#arrow)" />
                <text x="348" y="572" fill="#4a3a7a" fontSize="8" fontFamily="JetBrains Mono,monospace">shared by all</text>
              </svg>
            </div>
            <div style={{ marginTop: 12, color: "#3a5a7a", fontSize: 10 }}>→ solid line: direct dependency &nbsp;|&nbsp; - - dashed: optional/indirect dependency</div>
          </div>
        )}

        {/* ROADMAP */}
        {activeSection === "roadmap" && (
          <div className="section-content">
            <h2 style={{ fontFamily: "'Orbitron',sans-serif", color: "#00d4ff", marginBottom: 8, fontSize: 18 }}>Development Roadmap</h2>
            <p style={{ color: "#7a9aba", marginBottom: 28, lineHeight: 1.7, maxWidth: 680 }}>20-week phased plan. Each phase is independently compilable and testable. P0 modules must be complete before P1 begins. P2 (audio, networking) can run in parallel after Phase 3.</p>
            {roadmapPhases.map((phase, i) => (
              <div key={i} style={{ marginBottom: 24 }}>
                <div style={{ display: "flex", alignItems: "center", gap: 14, marginBottom: 12 }}>
                  <div style={{ width: 8, height: 8, borderRadius: "50%", background: phase.color, flexShrink: 0, boxShadow: `0 0 8px ${phase.color}` }} />
                  <div style={{ fontFamily: "'Orbitron',sans-serif", color: phase.color, fontSize: 12, letterSpacing: "0.1em" }}>{phase.phase}: {phase.title}</div>
                  <div style={{ color: "#3a5a7a", fontSize: 10 }}>{phase.duration}</div>
                  <div style={{ flex: 1, height: 1, background: "#1a2d4a" }} />
                </div>
                <div style={{ marginLeft: 22, display: "grid", gridTemplateColumns: "repeat(auto-fill,minmax(280px,1fr))", gap: 8 }}>
                  {phase.items.map((item, j) => (
                    <div key={j} style={{ background: "#0d1828", border: `1px solid ${phase.color}20`, borderLeft: `2px solid ${phase.color}60`, borderRadius: "0 6px 6px 0", padding: "10px 14px", color: "#9ab8d0", fontSize: 12, lineHeight: 1.5 }}>{item}</div>
                  ))}
                </div>
              </div>
            ))}
            <div style={{ marginTop: 16, padding: "16px 20px", background: "#0d1828", border: "1px solid #1a2d4a", borderRadius: 8, color: "#5a7a9a", lineHeight: 1.8, fontSize: 12 }}>
              <span style={{ color: "#00d4ff" }}>◈ Milestone gates: </span>Phase 0 → unit-tested math + render context. Phase 1 → "Hello Triangle" + sprite batch. Phase 2 → scene + shape cast demo. Phase 3 → physics sandbox. Phase 4 → animated skinned mesh. Phase 5 → 2-player networked demo.
            </div>
          </div>
        )}

        {/* PLATFORM */}
        {activeSection === "platform" && (
          <div className="section-content">
            <h2 style={{ fontFamily: "'Orbitron',sans-serif", color: "#00d4ff", marginBottom: 8, fontSize: 18 }}>Platform Strategy</h2>
            <p style={{ color: "#7a9aba", marginBottom: 28, lineHeight: 1.7, maxWidth: 680 }}>Single CMake codebase with compile-time platform switches. No separate codebases.</p>
            <div style={{ display: "grid", gridTemplateColumns: "1fr 1fr", gap: 16, marginBottom: 24 }}>
              {[
                { platform: "PC (Windows / Linux / macOS)", icon: "🖥", color: "#00d4ff", items: [["OpenGL", "3.3 Core Profile"], ["Window/Input", "GLFW 3.x"], ["Extension loader", "glad (generated)"], ["Threading", "std::thread / std::async"], ["Networking", "asio (header-only)"], ["Build", "CMake → static lib (.a/.lib)"], ["Test runner", "Catch2"]] },
                { platform: "Android (NDK r25+)", icon: "📱", color: "#34d399", items: [["OpenGL ES", "3.0 via EGL"], ["Window/Input", "ANativeWindow + AInputQueue"], ["Threading", "pthread / std::thread (NDK)"], ["Networking", "POSIX sockets (bionic)"], ["Build", "CMake + Android Gradle → .so"], ["Audio", "AAudio / OpenSL ES backend"], ["Test", "adb shell gtest runner"]] },
              ].map((p) => (
                <div key={p.platform} style={{ background: "#0d1828", border: `1px solid ${p.color}30`, borderRadius: 8, padding: "20px" }}>
                  <div style={{ fontSize: 20, marginBottom: 8 }}>{p.icon}</div>
                  <div style={{ color: p.color, fontWeight: 700, marginBottom: 16, fontSize: 13 }}>{p.platform}</div>
                  {p.items.map(([k, v]) => (
                    <div key={k} style={{ display: "flex", justifyContent: "space-between", padding: "6px 0", borderBottom: "1px solid #0f1e30" }}>
                      <span style={{ color: "#4a6a8a", fontSize: 11 }}>{k}</span>
                      <span style={{ color: "#c2d8f0", fontSize: 11 }}>{v}</span>
                    </div>
                  ))}
                </div>
              ))}
            </div>
            <h3 style={{ color: "#a78bfa", fontSize: 12, letterSpacing: "0.1em", marginBottom: 16 }}>COMPILE-TIME ABSTRACTION PATTERN</h3>
            <div style={{ background: "#060a10", border: "1px solid #1a2d4a", borderRadius: 8, padding: "20px", fontFamily: "JetBrains Mono,monospace", fontSize: 12, lineHeight: 1.9, color: "#7a9aba", overflowX: "auto" }}>
              <span style={{ color: "#4a6a8a" }}>{"// Platform header (nova/platform/platform.h)"}</span>{"\n"}
              <span style={{ color: "#e879f9" }}>#if </span><span style={{ color: "#fbbf24" }}>defined(NOVA_ANDROID)</span>{"\n"}
              {"  "}<span style={{ color: "#e879f9" }}>#include </span><span style={{ color: "#34d399" }}>"android/android_window.h"</span>{"\n"}
              {"  "}<span style={{ color: "#e879f9" }}>#define </span><span style={{ color: "#00d4ff" }}>NOVA_GL_HEADER </span><span style={{ color: "#34d399" }}>&lt;GLES3/gl3.h&gt;</span>{"\n"}
              <span style={{ color: "#e879f9" }}>#else</span>{"\n"}
              {"  "}<span style={{ color: "#e879f9" }}>#include </span><span style={{ color: "#34d399" }}>"desktop/glfw_window.h"</span>{"\n"}
              {"  "}<span style={{ color: "#e879f9" }}>#define </span><span style={{ color: "#00d4ff" }}>NOVA_GL_HEADER </span><span style={{ color: "#34d399" }}>"glad/glad.h"</span>{"\n"}
              <span style={{ color: "#e879f9" }}>#endif</span>{"\n\n"}
              <span style={{ color: "#4a6a8a" }}>{"// All engine code uses NOVA_GL_HEADER — zero ifdefs in business logic"}</span>
            </div>
            <div style={{ marginTop: 20, display: "grid", gridTemplateColumns: "repeat(3,1fr)", gap: 12 }}>
              {[
                { title: "Shared 100%", items: ["Math", "ECS / Scene", "Physics", "Collision", "Animation", "Asset Manager API"] },
                { title: "Thin Abstraction", items: ["Window creation", "Input events", "GL context (EGL vs GLFW)", "File I/O", "Thread model"] },
                { title: "Platform-Specific", items: ["GLFW (desktop only)", "ANativeActivity (Android)", "AAudio vs OpenAL", "Android asset_manager_open"] },
              ].map((col) => (
                <div key={col.title} style={{ background: "#0d1828", border: "1px solid #1a2d4a", borderRadius: 8, padding: "16px" }}>
                  <div style={{ color: "#a78bfa", fontSize: 11, fontWeight: 700, marginBottom: 10 }}>{col.title}</div>
                  {col.items.map((it) => (
                    <div key={it} style={{ color: "#7a9aba", fontSize: 11, padding: "4px 0", borderBottom: "1px solid #0f1e30" }}>{it}</div>
                  ))}
                </div>
              ))}
            </div>
          </div>
        )}
      </div>
    </div>
  );
}

const root = ReactDOM.createRoot(document.getElementById("root"));
root.render(<App />);
