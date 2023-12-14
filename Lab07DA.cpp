// Lab07DA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));
	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(400, 195));
	ball.setRadius(20);
	ball.applyImpulse(Vector2f(0, 20));
	world.AddPhysicsBody(ball);
	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);
	// Create the wall on the right
	PhysicsRectangle wall1;
	wall1.setSize(Vector2f(20, 600));
	wall1.setCenter(Vector2f(790, 300));
	wall1.setStatic(true);
	world.AddPhysicsBody(wall1);
	// Create the wall on the left
	PhysicsRectangle wall2;
	wall2.setSize(Vector2f(20, 600));
	wall2.setCenter(Vector2f(10, 300));
	wall2.setStatic(true);
	world.AddPhysicsBody(wall2);
	// Create the ceiling
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);
	//Create the rectangle obstacle
	PhysicsRectangle rectangleobstacle;
	rectangleobstacle.setSize(Vector2f(100, 120));
	rectangleobstacle.setCenter(Vector2f(400, 295));
	rectangleobstacle.setStatic(true);
	world.AddPhysicsBody(rectangleobstacle);
	
	
	int thudCount(0);
	int bangCount(0);

	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};

	rectangleobstacle.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "bang " << bangCount << endl;
		bangCount++;
		if (bangCount >= 3) {
			exit(0);
		}
	};

	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(wall1);
		window.draw(wall2);
		window.draw(ceiling);
		window.draw(rectangleobstacle);
		window.display();
	}
	

}
