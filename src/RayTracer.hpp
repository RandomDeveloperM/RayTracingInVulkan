#pragma once

#include "SceneList.hpp"
#include "UserSettings.hpp"
#include "Vulkan/RayTracing/Application.hpp"

class RayTracer final : public Vulkan::RayTracing::Application
{
public:

	VULKAN_NON_COPIABLE(RayTracer)

	RayTracer(const Vulkan::WindowConfig& windowConfig, bool vsync);
	~RayTracer();

protected:

	const Assets::Scene& GetScene() const override { return *scene_; }
	Assets::UniformBufferObject GetUniformBufferObject(VkExtent2D extent) const override;

	void OnDeviceSet() override;
	void CreateSwapChain() override;
	void DeleteSwapChain() override;
	void DrawFrame() override;
	void Render(VkCommandBuffer commandBuffer, uint32_t imageIndex) override;

	void OnKey(int key, int scancode, int action, int mods) override;
	void OnCursorPosition(double xpos, double ypos) override;
	void OnMouseButton(int button, int action, int mods) override;

private:

	void LoadScene(int sceneIndex);

	int sceneIndex_{};
	UserSettings userSettings_{};
	UserSettings previousSettings_{};
	SceneList::CameraInitialSate cameraInitialSate_{};

	std::unique_ptr<const Assets::Scene> scene_;
	std::unique_ptr<class UserInterface> userInterface_;

	double mouseX_{};
	double mouseY_{};
	bool mouseLeftPressed_{};

	float cameraX_{};
	float cameraY_{};
	double time_{};

	uint32_t totalNumberOfSamples_{};
	uint32_t numberOfSamples_{};
	bool resetAccumulation_{};
};
