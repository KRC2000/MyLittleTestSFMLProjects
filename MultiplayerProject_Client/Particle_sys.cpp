#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>

using namespace sf;
using namespace std;


//class ParticleSystem_fire : public Drawable
//{
//	Vector2f emiter{200, 300};
//	int part_amount = 15000;
//	Vector2f part_size{ 3, 3 };
//
//	struct Particle
//	{
//		float speed{0};
//		RectangleShape rect{ {1, 1} };
//		Vector2f velocity{ 0, 1 };
//		Time lifeTime = milliseconds(1000); // In milliseconds
//	};
//
//	vector<Particle> part_arr;
//
//public:
//	ParticleSystem_fire()
//	{
//		part_arr.reserve(part_amount);
//
//		for ( int i = 0; i < part_amount ; ++i)
//		{
//			Particle p;
//			p.rect.setSize(part_size);
//			p.rect.setFillColor({ (Uint8)(rand() % 55 + 200), (Uint8)(rand() % 150), 0 });
//			p.rect.setPosition(emiter);
//			p.rect.move({ (float)(rand() % 20 - 10), (float)(rand() % 20 - 10) });
//			p.speed = rand() % 60 + 120;
//			p.velocity = { 0, -1 };
//			p.lifeTime = milliseconds(rand() % 1000 + 500);
//
//			part_arr.push_back(p);
//		}
//	}
//
//	void update(Time cycleTime)
//	{
//		for (int i = 0; i < part_arr.size(); ++i)
//		{
//			part_arr[i].rect.move(part_arr[i].speed * part_arr[i].velocity.x * cycleTime.asSeconds(), part_arr[i].speed * part_arr[i].velocity.y * cycleTime.asSeconds());
//			part_arr[i].lifeTime -= cycleTime;
//
//			if (part_arr[i].lifeTime < Time::Zero)
//			{
//				part_arr[i].rect.setFillColor({ (Uint8)(rand() % 55 + 200), (Uint8)(rand() % 150), 0 });
//				part_arr[i].rect.setPosition(emiter);
//				part_arr[i].rect.move({ (float)(rand() % 40 - 20), (float)(rand() % 20 - 10) });
//				part_arr[i].speed = rand() % 60 + 120;
//				part_arr[i].lifeTime = milliseconds(rand() % 1000 + 500);
//			}
//		}
//	}
//
//	void setEmiterPos(Vector2f newPos)
//	{
//		emiter = newPos;
//	}
//private:
//
//	virtual void draw(RenderTarget& target, RenderStates states) const
//	{
//		for (int i = 0; i < part_arr.size(); i++)
//		{
//			target.draw(part_arr[i].rect);
//		}
//	}
//};

class ParticleSystem : public Drawable 
{
	struct ParticleDataObj
	{
	public:
		int minAngle = 0;
		int maxAngle = 360 ;

		int minSpeed = 30;
		int maxSpeed = 70;

		int minLifeTimeMilliseconds = 2500;
		int maxLifeTimeMilliseconds = 4000;



		int quadIndex = 0;
		float speed;
		Vector2f speedVec;
		Time lifeTime, lifeTime_left;

		ParticleDataObj()
		{
			resetObjVars();
		}

		void resetObjVars()
		{
			speed = minSpeed + (rand() % (maxSpeed - minSpeed));
			float angleRad = ( rand() % (maxAngle - minAngle) + minAngle ) * 3.14159 / 180.f;
			cout << (rand() % (maxAngle - minAngle) + minAngle) << endl;
			speedVec = { cos(angleRad) * speed , sin(angleRad) * speed };
			lifeTime = milliseconds( rand() % (maxLifeTimeMilliseconds - minLifeTimeMilliseconds) + minLifeTimeMilliseconds );
			lifeTime_left = lifeTime;
		}
	};

	vector<Vertex> vertexVec;
	vector<ParticleDataObj> particleDataVec;
	Texture t;
	Clock resetTimer;

	FloatRect emitterRect = { 400 , 300, 20, 30 };
	int particlesAmount = 0;

	int default_particlesAmount = 1000;
	Vector2f default_particleSize = { 30, 30 };
public:
	ParticleSystem() 
	{ 
		for (int i = 0; i < default_particlesAmount; i++)
		{
			addParticle();
			t.loadFromFile("fire.png");
		}
	};
	virtual ~ParticleSystem() {};

	void update(Time cycleTime, Vector2f force = {0, 0})
	{
		for (int i = 0; i < particlesAmount; i++)
		{
			particleDataVec[i].speedVec += force * cycleTime.asSeconds();

			vertexVec[i * 4].position += particleDataVec[i].speedVec * cycleTime.asSeconds();
			vertexVec[i * 4 + 1].position += particleDataVec[i].speedVec * cycleTime.asSeconds();
			vertexVec[i * 4 + 2].position += particleDataVec[i].speedVec * cycleTime.asSeconds();
			vertexVec[i * 4 + 3].position += particleDataVec[i].speedVec * cycleTime.asSeconds();

			float remainingLifeTimeRatio = particleDataVec[i].lifeTime_left / particleDataVec[i].lifeTime;
			//setParticleTransperency(i, remainingLifeTimeRatio * 255);
			//setParticleSize(i, remainingLifeTimeRatio * default_particleSize);

			particleDataVec[i].lifeTime_left -= cycleTime;
			if (particleDataVec[i].lifeTime_left <= Time::Zero)
			{
				particleDataVec[i].resetObjVars();
				setParticlePos(i, { rand() % (int)emitterRect.width + emitterRect.left, rand() % (int)emitterRect.height + emitterRect.top });
			}
		}
	}
	void setEmitterPos(Vector2f newPos) { emitterRect.left = newPos.x; emitterRect.top = newPos.y; };
	virtual void draw(RenderTarget& target, RenderStates states) const
	{
		states.texture = &t;
		target.draw(&vertexVec[0], vertexVec.size(), sf::Quads, states);
	};

private:
	void setParticleSize(int particleIndex, Vector2f newSize)
	{
		vertexVec[particleIndex * 4 + 1].position.x = vertexVec[particleIndex * 4].position.x + newSize.x;
		vertexVec[particleIndex * 4 + 2].position = vertexVec[particleIndex * 4].position + newSize;
		vertexVec[particleIndex * 4 + 3].position.y = vertexVec[particleIndex * 4].position.y + newSize.y;
	};
	void setParticleTransperency(int particleIndex, int newAlpha)
	{
		vertexVec[particleIndex * 4].color.a = newAlpha;
		vertexVec[particleIndex * 4 + 1].color.a = newAlpha;
		vertexVec[particleIndex * 4 + 2].color.a = newAlpha;
		vertexVec[particleIndex * 4 + 3].color.a = newAlpha;
	};
	void setParticlePos(int particleIndex, Vector2f newPos)
	{
		vertexVec[particleIndex * 4].position = newPos;
		vertexVec[particleIndex * 4 + 1].position = { newPos.x + default_particleSize.x, newPos.y };
		vertexVec[particleIndex * 4 + 2].position = { newPos.x + default_particleSize.x, newPos.y + default_particleSize.y };
		vertexVec[particleIndex * 4 + 3].position = { newPos.x, newPos.y + default_particleSize.y };
	};
	void moveParticles(Vector2f offset)
	{
		for (auto& vertex : vertexVec)
		{
			vertex.position += offset;
		}
	};
	void addParticle() 
	{
		Vertex ul; ul.position = { 0, 0 };
		Vertex ur; ur.position = { default_particleSize.x, 0 };
		Vertex dr; dr.position = { default_particleSize.x, default_particleSize.y };
		Vertex dl; dl.position = { 0, default_particleSize.y };

		ul.position += {emitterRect.left, emitterRect.top };
		ur.position += {emitterRect.left, emitterRect.top };
		dr.position += {emitterRect.left, emitterRect.top };
		dl.position += {emitterRect.left, emitterRect.top };

		ul.texCoords = { 0, 0 };
		ur.texCoords = { (float)t.getSize().x, 0 };
		dr.texCoords = { (float)t.getSize().x, (float)t.getSize().y };
		dl.texCoords = { 0, (float)t.getSize().y };

		/*ul.color = getRandomColor();
		ur.color = getRandomColor();
		dr.color = getRandomColor();
		dl.color = getRandomColor();*/

		vertexVec.push_back(ul);
		vertexVec.push_back(ur);
		vertexVec.push_back(dr);
		vertexVec.push_back(dl);

		ParticleDataObj obj;
		obj.quadIndex = particlesAmount + 1;
		particleDataVec.push_back(obj);

		particlesAmount++;
	};
	Color getRandomColor() 
	{
		return { (Uint8)(rand() % 255), (Uint8)(rand() % 255) , (Uint8)(rand() % 255) };
	};
};


Time cycleTime;
Clock cycleTimer;

int main()
{
	srand(time(NULL));
	RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

	ParticleSystem part_sys;
	//ParticleSystem_fire part_sys;


	while (window.isOpen())
	{
		cycleTime = cycleTimer.restart();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		part_sys.update(cycleTime, {0 , 0});
		//part_sys.update(cycleTime);
		//part_sys.setEmiterPos(window.mapPixelToCoords(Mouse::getPosition(window)));
		part_sys.setEmitterPos(window.mapPixelToCoords(Mouse::getPosition(window)));

		window.clear(Color::Cyan);
		window.draw(part_sys);
		window.display();
	}

	return 0;
};
