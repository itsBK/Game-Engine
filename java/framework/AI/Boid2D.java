package framework.AI;

import framework.gameObject.DynamicObject2D;
import framework.math.Vector2;
import framework.math.bounds.Circle;
import framework.math.bounds.Line2D;

public class Boid2D extends DynamicObject2D {

    public float angle;
    public float maxSpeed;
    private float screenWidth;
    private float screenHeight;

    public Vector2 ahead;
    public Line2D aheadLine;

    public Vector2 avoidance;
    public Vector2 alignment;
    public Vector2 cohesion;


    public Boid2D(float x, float y, float radius, float maxSpeed,
                  float dirX, float dirY, float sceneWidth, float sceneHeight) {

        super(x, y, radius);
        this.maxSpeed = maxSpeed;
        this.screenWidth = sceneWidth;
        this.screenHeight = sceneHeight;

        this.velocity.set(dirX, dirY).nor().mul(maxSpeed);
        this.angle = this.velocity.angle();

        this.ahead = new Vector2(position).add(velocity);
        this.aheadLine = new Line2D(position, ahead);

        this.avoidance = new Vector2();
        this.alignment = new Vector2();
        this.cohesion = new Vector2();
    }

    public void update(float deltaTime) {
        accel.set(avoidance).add(alignment).add(cohesion);
        velocity.add(accel.x * deltaTime, accel.y * deltaTime).nor().mul(maxSpeed);

        this.angle = velocity.angle();
        if (angle < 0) angle += 360f;
        if (angle > 360f) angle -= 360f;

        position.add(velocity.x * deltaTime, velocity.y * deltaTime);

        if (position.x < 0) position.x += screenWidth;
        if (position.y < 0) position.y += screenHeight;
        if (position.x > screenWidth) position.x -=screenWidth;
        if (position.y > screenHeight) position.y -= screenHeight;

        ((Circle) bounds).center.set(position);

        this.ahead.set(position).add(velocity);
        this.aheadLine.start.set(position);
        this.aheadLine.end.set(ahead);
    }
}
