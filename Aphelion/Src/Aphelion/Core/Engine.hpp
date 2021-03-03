#pragma once
#include <memory>
#include <vector>

#include "Core.hpp"
#include "System.hpp"

namespace ap {
// class System;

/**
 * Engine is the runtime of the application. The user creates
 * an instance of this class and passes whatever systems they
 * require from it
 */
class APHELION_API Engine {
 public:
  static Engine& Get();

  void Run();
  void Loop(float ts);

  void AddSystem(std::unique_ptr<System>&& system);
  void AddSystems(std::vector<std::unique_ptr<System>>&& systems);

 private:
  Engine();

  std::vector<std::unique_ptr<System>> m_systems;
};
}  // namespace ap