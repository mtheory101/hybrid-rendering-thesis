#pragma once

#include <glm/glm.hpp>

#include <memory>
#include <string>
#include <functional>

namespace Render
{
	class GBuffer; typedef std::shared_ptr<GBuffer> GBufferPtr;
	class DeferredRender; typedef std::shared_ptr<DeferredRender> DeferredRenderPtr;
}
namespace Raytracer
{
	class OptixRender; typedef std::shared_ptr<OptixRender> OptixRenderPtr;
}
namespace File
{
	class ShaderLoader; typedef std::shared_ptr<ShaderLoader> ShaderLoaderPtr;
	class TextureLoader; typedef std::shared_ptr<TextureLoader> TextureLoaderPtr;
	class MaterialLoader; typedef std::shared_ptr<MaterialLoader> MaterialLoaderPtr;
}
namespace Scene
{
	class SceneManager; typedef std::shared_ptr<SceneManager> SceneManagerPtr;
	class FirstPersonCamera; typedef std::shared_ptr<FirstPersonCamera> FirstPersonCameraPtr;
}

class Kernel; typedef std::shared_ptr<Kernel> KernelPtr;
class Kernel
{
public:
	static KernelPtr getSingleton();
	static void Shutdown();
	~Kernel();

	void config(const std::string &resource_dir);
	void init(int argc, char** argv);
	void initScene(); //Will be deprecated at some point...

	void run(int start_time, std::function<void()> main_loop_body);
	void exit() { running = false; }
	bool isRunning() const { return running; }

	void update(float dt);
	void render();
	void reshape(int w, int h);
	void inputKeyDown(unsigned char key, int x, int y);
	void inputKeyUp(unsigned char key, int x, int y);
	void input(int key, int x, int y);
	void motion(int x, int y);
	void mousePressed(int button, int state, int x, int y);

	int getPrevTime(int cur_time) { auto tmp_time = prev_time; prev_time = cur_time; return tmp_time; }
	int getStartTime() const { return start_time; }
	int getElapsedTime(int cur_time) const { return cur_time - start_time; }
	int getTimeSincePrevFrame(int cur_time) { return cur_time - getPrevTime(cur_time); }

public:
	const std::string &getResourceDir() const { return resource_dir; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getDepth() const { return depth; }
	int getRefreshRate() const { return refresh_rate; }
	int getLogicUpdateRate() const { return logic_update_rate; }
	int getFullscreen() const { return fullscreen; }
	int getGameMode() const { return game_mode; }
	std::string getGameModeString() const;
	int getOpenGLVersionMajor() const;
	int getOpenGLVersionMinor() const;
	std::string getOpenGLVersionString() const;

public:
	Render::GBufferPtr getGBuffer() const { return g_buffer; }
	Render::DeferredRenderPtr getRenderer() const { return renderer; }
	Raytracer::OptixRenderPtr getRaytracer() const { return raytracer; }
	File::ShaderLoaderPtr getShaderLoader() const { return shader_loader; }
	File::TextureLoaderPtr getTextureLoader() const { return tex_loader; }
	File::MaterialLoaderPtr getMaterialLoader() const { return mat_loader; }
	Scene::SceneManagerPtr getSceneManager() const { return scene; }
	Scene::FirstPersonCameraPtr getActiveCamera() const { return camera; }

private:
#if(_MSC_VER >= 1700)
	friend class std::_Ref_count_obj<Kernel>;
#else
	friend class std::tr1::_Ref_count_obj<Kernel>;
#endif
	static KernelPtr singleton;
	Kernel();

	std::string resource_dir;

	int width;
	int height;
	int depth;
	int refresh_rate;
	int logic_update_rate;
	int fullscreen;
	int game_mode;

	bool running;
	int start_time;
	int prev_time;

private:
	Render::GBufferPtr g_buffer;
	Render::DeferredRenderPtr renderer;
    Raytracer::OptixRenderPtr raytracer;
	File::ShaderLoaderPtr shader_loader;
	File::TextureLoaderPtr tex_loader;
	File::MaterialLoaderPtr mat_loader;
	Scene::SceneManagerPtr scene;
    Scene::FirstPersonCameraPtr camera;
	
	const static int MAX_KEYS = 256;
	bool keystatus[MAX_KEYS];
	
	struct mouseDef
	{
		bool leftPressed;
		bool rightPressed;
		glm::ivec2 coords;
	} mouse;
};
