package framework.AI;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import javax.microedition.khronos.opengles.GL10;

import framework.gl.vertices.Vertices;
import framework.math.OverlapTester;
import framework.math.bounds.Circle;

public class Boids2D {

    private Vertices vertices;
    private Random rand;
    private List<Boid2D> boids;
    private List<Boid2D> nearby;
    public Boid2D current;
    private int numBoids;
    private float maxSpeed;
    private float maxViewingDistance;

    public boolean avoidance = false;
    public boolean alignment = false;
    public boolean cohesion  = false;


    public Boids2D(int numBoids, float radius, float maxSpeed, float maxViewingDistance,
                   float sceneWidth, float sceneHeight) {

        boids = new ArrayList<>(numBoids);
        nearby = new ArrayList<>();
        this.numBoids = numBoids;
        this.maxSpeed = maxSpeed;
        this.maxViewingDistance = maxViewingDistance;

        float x, y;
        float dirX, dirY;
        for (int i = 0; i < numBoids; i++) {
            x = rand.nextFloat() * sceneWidth;
            y = rand.nextFloat() * sceneHeight;
            dirX = rand.nextFloat() * 2 - 1;
            dirY = rand.nextFloat() * 2 - 1;
            boids.add(new Boid2D(x, y, radius, maxSpeed, dirX, dirY, sceneWidth, sceneHeight));
        }
    }


    public void update(float deltaTime) {
        int len = boids.size();



        //calculate forces
        for (int i = 0; i < numBoids; i++) {
            current = boids.get(i);
            nearby.clear();
            current.avoidance.set(0, 0);
            current.alignment.set(0, 0);
            current.cohesion.set(0, 0);

            for (int j = 0; j < numBoids; j++) {
                if (j == i)
                    continue;

                if (current.position.distSquared(boids.get(j).position)
                        < maxViewingDistance * maxViewingDistance) {
                    nearby.add(boids.get(j));
                }
            }

            len = nearby.size();

            if (avoidance) {
                float distClosest = 100;
                Boid2D closest = null;

                for (int j = 0; j < len; j++) {
                    if (OverlapTester.overlapCircleLine2D((Circle) nearby.get(j).bounds, current.aheadLine)) {

                        if (closest == null) {
                            closest = nearby.get(j);
                            distClosest = current.position.dist(closest.position);

                        } else if (distClosest > current.position.dist(nearby.get(j).position)) {
                            closest = nearby.get(j);
                            distClosest = current.position.dist(closest.position);
                        }
                    }
                }

                if (closest != null) {
                    current.avoidance.set(current.ahead).sub(closest.position)
                            .nor().mul(maxSpeed);
                }
            }

            if (alignment) {
                for (int j = 0; j < len; j++)
                    current.alignment.add(nearby.get(j).velocity);
                current.alignment.nor().mul(1f / 8);
            }

            if (cohesion) {
                for (int j = 0; j < len; j++)
                    current.cohesion.add(nearby.get(j).position).sub(current.position);
                current.cohesion.sub(current.velocity);
                current.cohesion.nor().mul(1f / 8);
            }
        }

        for (int i = 0; i < len; i++)
            boids.get(i).update(deltaTime);
    }

    public void draw(GL10 gl) {
        Boid2D boid;

        for (int i = 0; i < numBoids; i++) {
            boid = boids.get(i);
            gl.glTranslatef(boid.position.x, boid.position.y, 0);
            gl.glRotatef(boid.angle, 0, 0, 1);
            gl.glColor4f(0.03f, 0.80f, 0.90f, 1);

            vertices.draw();
            gl.glLoadIdentity();
        }
    }

    public void setVertices(Vertices vertices) {
        this.vertices = vertices;
    }

    public Vertices getVertices() {
        return vertices;
    }

    public List<Boid2D> getAllBoids() {
        return boids;
    }

    public List<Boid2D> getNearbyBoids(int index) {
        return nearby;
    }

    public Boid2D getBoid(int index) {
        return boids.get(index);
    }
}
