#pragma once

#include <functional>
#include <future>
#include <vector>

#include <mutex>

struct GLFWwindow;

namespace hex::init {

    using TaskFunction = std::function<bool()>;

    class WindowSplash {
    public:
        WindowSplash();
        ~WindowSplash();

        bool loop();

        void addStartupTask(const std::string &taskName, const TaskFunction &task) {
            this->m_tasks.emplace_back(taskName, task);
        }

        [[nodiscard]] const std::string &getGPUVendor() const { return this->m_gpuVendor; }

    private:
        GLFWwindow *m_window;
        std::mutex m_progressMutex;
        float m_progress = 0;
        std::string m_currTaskName;

        void initGLFW();
        void initImGui();

        void exitGLFW();
        void exitImGui();

        std::future<bool> processTasksAsync();

        std::vector<std::pair<std::string, TaskFunction>> m_tasks;

        std::string m_gpuVendor;
    };

}
