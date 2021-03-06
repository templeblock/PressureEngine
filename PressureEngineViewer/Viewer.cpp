#include "PressureEngineCore/PressureEngine.h"

namespace PressureEngineViewer {

	using namespace Pressure;

	class EngineViewer {

	private: 
		PressureEngine engine;

		std::vector<Entity> entities;
		std::vector<Light> lights;
		ParticleSystem* particleSystem;
		std::vector<Water> waters;

		Random<float> r;

	public:
		EngineViewer() : r(-2, 2) {
			engine.init();
			init();
			loop();
		}

		void init() {
			//TexturedModel mclaren = engine.loadModel("McLaren570S", "default.png");
			//entities.emplace_back(mclaren, Vector3f(0), Vector3f(0), 0.1);

			// Island
			RawModel islandModel = engine.loadObjModel("Island");
			ModelTexture islandTexture(engine.loadTexture("Island.png"));
			islandTexture.setShineDamper(10);
			islandTexture.setReflectivity(.1f);
			TexturedModel island(islandModel, islandTexture);
			entities.emplace_back(island, Vector3f(0), Vector3f(0, 0, 0), 8.f);

			RawModel pathModel = engine.loadObjModel("Path");
			ModelTexture pathTexture = engine.loadTexture("Path.png");
			pathTexture.setFakeLighting(true);
			TexturedModel path(pathModel, pathTexture);
			entities.emplace_back(path, Vector3f(0), Vector3f(0), 8.f);

			RawModel jettyModel = engine.loadObjModel("Jetty");
			ModelTexture jettyTexture(engine.loadTexture("Jetty.png"));
			jettyTexture.setShineDamper(10);
			jettyTexture.setReflectivity(.5f);
			TexturedModel jetty(jettyModel, jettyTexture);
			entities.emplace_back(jetty, Vector3f(-10, 0.5f, 4), Vector3f(0, 185, 0), 2.f);

			RawModel treeModel = engine.loadObjModel("Tree");
			treeModel.setWindAffected(true);
			ModelTexture treeTexture = engine.loadTexture("Tree.png");
			TexturedModel tree(treeModel, treeTexture);
			entities.emplace_back(tree, Vector3f(-31.5, 12.2, -14), Vector3f(3, 0, 0), 8.0);

			RawModel houseModel = engine.loadObjModel("House");
			ModelTexture houseTexture = engine.loadTexture("House.png");
			TexturedModel house(houseModel, houseTexture);
			entities.emplace_back(house, Vector3f(22, 0.2, -3), Vector3f(0, -84, 0), 1.8);

			RawModel gardenModel = engine.loadObjModel("Garden");
			gardenModel.setWindAffected(true);
			ModelTexture gardenTexture = engine.loadTexture("Garden.png");
			TexturedModel garden(gardenModel, gardenTexture);
			entities.emplace_back(garden, Vector3f(30, 0.9, 12), Vector3f(2, 50, -2), 1.5);
			entities.emplace_back(garden, Vector3f(24, 0.8, 16), Vector3f(5, 20, 0), 1.5);

			RawModel benchModel = engine.loadObjModel("Bench");
			ModelTexture benchTexture = engine.loadTexture("Bench.png");
			TexturedModel bench(benchModel, benchTexture);
			entities.emplace_back(bench, Vector3f(18, 1.85, 5), Vector3f(0, -86, 0), 1.4);

			RawModel barrowModel = engine.loadObjModel("Wheelbarrow");
			ModelTexture barrowTexture = engine.loadTexture("Wheelbarrow.png");
			TexturedModel barrow(barrowModel, barrowTexture);
			entities.emplace_back(barrow, Vector3f(28, 0.60, 5), Vector3f(0, -60, 0), 1.6);

			RawModel bushModel = engine.loadObjModel("Bush");
			bushModel.setWindAffected(true);
			ModelTexture bushTexture = engine.loadTexture("Tree.png");
			RawModel bush2Model = engine.loadObjModel("Bush2");
			bush2Model.setWindAffected(true);
			TexturedModel bush(bushModel, bushTexture);
			TexturedModel bush2(bush2Model, bushTexture);
			// Behind house
			entities.emplace_back(bush2, Vector3f(34.5, 1, 0), Vector3f(0, 0, 0), 10.0);
			entities.emplace_back(bush, Vector3f(37.5, 1, 4), Vector3f(0, 70, 0), 9.0);
			entities.emplace_back(bush, Vector3f(33.5, 1, 8), Vector3f(0, 45, 0), 9.5);
			// Close gravestone
			entities.emplace_back(bush2, Vector3f(-24, 1, -18), Vector3f(0, 10, 0), 9.5);
			entities.emplace_back(bush2, Vector3f(-20, .8, -17.5), Vector3f(0, 154, 0), 8.5);
			// House frontside
			entities.emplace_back(bush2, Vector3f(11, 1.5, -10), Vector3f(0, 154, 0), 10);
			entities.emplace_back(bush2, Vector3f(6, 1.5, -8), Vector3f(0, 45, 0), 9);
			entities.emplace_back(bush, Vector3f(10, 1.5, -5), Vector3f(0, 154, 0), 7);
			entities.emplace_back(bush, Vector3f(6, 1.5, -3), Vector3f(0, 270, 0), 6);
			entities.emplace_back(bush, Vector3f(2, 1.3, -5.7), Vector3f(0, 47, 0), 7.5);

			RawModel lampModel = engine.loadObjModel("Lamp");
			ModelTexture lampTexture = engine.loadTexture("Lamp.png");
			lampTexture.setTransparency(true);
			TexturedModel lamp(lampModel, lampTexture);
			entities.emplace_back(lamp, Vector3f(14, 3.5, -2.6), Vector3f(0, -84, 0), 1.2);

			RawModel tree2Model = engine.loadObjModel("Tree2");
			tree2Model.setWindAffected(true);
			TexturedModel tree2(tree2Model, treeTexture);
			entities.emplace_back(tree2, Vector3f(32.5, 12.4, -10.5), Vector3f(0, 0, 0), 8.0);

			RawModel tombstoneModel = engine.loadObjModel("Tombstone");
			ModelTexture tombstoneTexture(engine.loadTexture("Tombstone.png"));
			TexturedModel tombstone(tombstoneModel, tombstoneTexture);
			entities.emplace_back(tombstone, Vector3f(-27, .3, -13.7), Vector3f(0, 88, 0), 1.2);

			RawModel wellModel = engine.loadObjModel("Well");
			ModelTexture wellTexture(engine.loadTexture("Well.png"));
			TexturedModel well(wellModel, wellTexture);
			entities.emplace_back(well, Vector3f(4, 0.1, 18), Vector3f(0, 195, 0), 1.6);

			TexturedModel windmill = engine.loadModel("Windmill", "Windmill.png");
			entities.emplace_back(windmill, Vector3f(13, 0, 17), Vector3f(0, 10, 0), 4);
			TexturedModel windmillblades = engine.loadModel("Windmillblades", "Windmillblades.png");
			entities.emplace_back(windmillblades, Vector3f(13.45, 10.35, 19.5), Vector3f(0, 10, 0), 4);
			entities.back().setRotationSpeed(0, 0, -0.4);

			RawModel rackModel = engine.loadObjModel("Fishingrack");
			ModelTexture rackTexture = engine.loadTexture("Fishingrack.png");
			TexturedModel rack(rackModel, rackTexture);
			entities.emplace_back(rack, Vector3f(-3, 0.4, 16), Vector3f(0, 150, 0), 1);

			// Fences
			RawModel fenceModel = engine.loadObjModel("Fence");
			RawModel fence2Model = engine.loadObjModel("Fence2");
			ModelTexture fenceTexture = engine.loadTexture("Jetty.png");
			TexturedModel fence(fenceModel, fenceTexture);
			TexturedModel fence2(fence2Model, fenceTexture);
			entities.emplace_back(fence, Vector3f(-7, 0.3, 19), Vector3f(0, 145, 0), 2.7);
			entities.emplace_back(fence2, Vector3f(-0.2, 0.1, 21.5), Vector3f(0, 173, 0), 2.7);
			entities.emplace_back(fence, Vector3f(7, -0.1, 22.5), Vector3f(0, 173, 0), 2.7);
			entities.emplace_back(fence, Vector3f(14, -0.4, 23), Vector3f(0, 175, 0), 2.7);
			entities.emplace_back(fence2, Vector3f(21, -0.6, 23), Vector3f(0, 183, 0), 2.7);
			entities.emplace_back(fence, Vector3f(28, -0.6, 22), Vector3f(0, 195, 0), 2.7);
			entities.emplace_back(fence, Vector3f(34, -0.6, 19), Vector3f(0, 220, 0), 2.7);
			entities.emplace_back(fence, Vector3f(38, -0.3, 13), Vector3f(0, 250, 0), 2.7);
			entities.emplace_back(fence2, Vector3f(40, 0.2, 6), Vector3f(0, 260, 0), 2.7);

			// Stones			
			RawModel stoneModels[3] = { engine.loadObjModel("Stone"), engine.loadObjModel("Stone2"), engine.loadObjModel("Stone3") };
			ModelTexture stoneTexture = engine.loadTexture("Stone.png");
			TexturedModel stones[3] = { { stoneModels[0], stoneTexture }, { stoneModels[1], stoneTexture }, { stoneModels[2], stoneTexture } };

			entities.emplace_back(stones[0], Vector3f(-41.2, -1, .6), Vector3f(10, 50, 10), 2.8);
			entities.emplace_back(stones[1], Vector3f(-41, -1.4, 3.5), Vector3f(20), 3.3);
			entities.emplace_back(stones[2], Vector3f(-40.5, -.6, 5), Vector3f(-10), 1.6);
			entities.emplace_back(stones[2], Vector3f(-40.2, -2.2, 2), Vector3f(-10, 70, 0), 1.6);

			entities.emplace_back(stones[1], Vector3f(-30, -7.2, 1), Vector3f(-10, 70, 0), 1);
			entities.emplace_back(stones[0], Vector3f(-26, -5.9, 9), Vector3f(-10, 70, 0), .6);
			entities.emplace_back(stones[2], Vector3f(-21, -5.2, 13), Vector3f(-10, 70, 0), .6);

			//entities.emplace_back(stones[0], Vector3f(-12, 0.3, -20), Vector3f(0, 0, 0), 2.3);

			if (std::stoi(Properties::get("renderGrass")) == 1) {
				RawModel grassModel = engine.loadObjModel("Grass");
				grassModel.setWindAffected(true);
				RawModel grass2Model = engine.loadObjModel("Grass2");
				grass2Model.setWindAffected(true);
				ModelTexture grassTexture(engine.loadTexture("Grass.png"));
				TexturedModel grass(grassModel, grassTexture);
				TexturedModel grass2(grass2Model, grassTexture);
				setGrassPatch(-38, 1, -12, grass, grass2, -0.2, 0);
				setGrassPatch(-39.5, 1.2, -9, grass, grass2, -0.25, .05);
				setGrassPatch(-40, 1.1, -5, grass, grass2, -0.45, -.25);
				setGrassPatch(-39, 0.6, 12, grass, grass2, -0.17, .2);
				setGrassPatch(-39, 0.75, 15, grass, grass2, -0.17, .2);
				setGrassPatch(-38, 0.75, 18, grass, grass2, -0.05, 0.15);
				setGrassPatch(-35, 0.7, 20, grass, grass2, -0.10, 0.15);
				setGrassPatch(-31, 0.8, 22, grass, grass2, 0.10, 0.15);
				setGrassPatch(-28, 0.8, 22, grass, grass2, -0.15, 0.15);
				setGrassPatch(-25, 0.7, 22, grass, grass2, 0.10, 0.25);
				setGrassPatch(-22, 0.6, 22, grass, grass2, 0.10, 0.30);
				setGrassPatch(-19, 0.6, 22, grass, grass2, 0.10, 0.15);
				setGrassPatch(-16, 0.7, 22, grass, grass2, 0.20, 0.25);
				setGrassPatch(-13, .5, 20, grass, grass2, 0.20, 0.3);
				setGrassPatch(-8, 0.7, 22, grass, grass2, -0.20, 0.3);

				setGrassPatch(32.5, 0.2, -4, grass, grass2, 0.05, -0.1);
				setGrassPatch(36.5, 0.5, -4, grass, grass2, 0.2, -0.3);
				setGrassPatch(37.5, 2, -8, grass, grass2, 0.7, -0.7);
				setGrassPatch(38.5, 0.3, 0, grass, grass2, 0.1, -0.2);
				setGrassPatch(32.5, 0.2, 4, grass, grass2, 0, 0);

				setGrassPatch(-18, 0, -18, grass, grass2, 0, -.2);
				setGrassPatch(-14, 0, -17, grass, grass2, 0, -.1);
				setGrassPatch(0, .8, -10, grass, grass2, .1, -.2);
			}

			// Lights
			lights.emplace_back(Vector3f(100000, 150000, 200000), Vector3f(1));
			lights.emplace_back(Vector3f(14, 3.5, -2.6), Vector3f(.8, 0.5, 0.25), Vector3f(.5, .4, .4));

			// Waters
			waters.emplace_back(engine.generateWater(Vector3f(-41, 0, -13)));
			waters.emplace_back(engine.generateWater(Vector3f(-41, 0, 3)));
			waters.emplace_back(engine.generateWater(Vector3f(-25, 0, -13)));
			waters.emplace_back(engine.generateWater(Vector3f(-25, 0, 3)));
			waters.emplace_back(engine.generateWater(Vector3f(-9, 0, -5)));

			ParticleTexture particleTex = engine.loadParticleTexture("WaterParticles.png", 4, false);
			particleSystem = new ParticleSystem(particleTex, 128, (Vector3f&)Vector3f(-.09, 0, 0), 0.01, 1.4 * 60);
		}

		void loop() {
			long lastTime = Math::getTimeNano();
			double ns = 1000000000. / PRESSURE_TICKRATE;
			double delta = 0;
			long timer = Math::getTimeMillis();
			int frames = 0;
			long now;

			while (!engine.getWindow().isClosing()) {
				now = Math::getTimeNano();
				delta += (now - lastTime) / ns;
				lastTime = now;

				while (delta >= 1) {
					tick();
					delta--;
				}

				if (!engine.getWindow().isClosing())
					render();
				frames++;

#ifdef PRESSURE_DEBUG
				if (Math::getTimeMillis() - timer > 1000) {
					timer += 1000;

					PRESSURE_LOG(LOG_INFO, std::string("FPS: ") + std::to_string(frames));
					frames = 0;
				}
#endif
			}
		}

		void tick() {
			if (particleSystem)
				particleSystem->generateParticles((Vector3f&)Vector3f(-41, 0, 3), Vector3f(.2, .1, 2));
			engine.tick();
			for (auto& entity : entities) {
				entity.tick();
			}

			if (Keyboard::isPressed(GLFW_KEY_ESCAPE))
				engine.getWindow().close();

			if (Keyboard::isPressed(GLFW_KEY_K))
				if (Log::ReportingLevel() == LOG_INFO)
					Log::ReportingLevel() = LOG_WARNING;
				else
					Log::ReportingLevel() = LOG_INFO;

		}

		void render() {
			engine.process(entities);
			engine.process(waters);
			engine.process(lights);
			//GuiTexture gui(3, (Vector2f&)Vector2f(0.5), (Vector2f&)Vector2f(0.5), false);
			//engine.process(gui);
			engine.render();
		}

		void terminate() {
			engine.terminate();
		}

	private:
		void setGrassPatch(const float x, const float y, const float z, const TexturedModel& grass, const TexturedModel& grass2, const float slopeX = 0.f, const float slopeZ = 0.f) {			
			if (false) { // If i want to render grass as planes.
				RawModel model = engine.loadObjModel("Plane");
				ModelTexture def = engine.loadTexture("default.png");
				TexturedModel plane(model, def);
				entities.emplace_back(plane, Vector3f(x, y, z), Vector3f(180.0 / Math::PI * atan(-slopeZ / 2), 0, 180.0 / Math::PI * atan(slopeX / 2)), 2.0f);
			} else {
				float offsetX, offsetZ, offsetY;
				for (int i = 0; i < 4; i++) {
					offsetX = r.next();
					offsetZ = r.next();
					offsetY = offsetX/2 * slopeX + offsetZ/2 * slopeZ;
					if (i < 2)
						entities.emplace_back(grass, Vector3f(x + offsetX, y + offsetY, z + offsetZ), Vector3f(0, r.next() * 180, 0), 1.0 + 0.3 * r.next());
					else
						entities.emplace_back(grass2, Vector3f(x + offsetX, y + offsetY, z + offsetZ), Vector3f(0, r.next() * 180, 0), 1.0 + 0.3 * r.next());
				}
			}
		}

	};

}

int main() {

	PressureEngineViewer::EngineViewer e;

	return 0;

}