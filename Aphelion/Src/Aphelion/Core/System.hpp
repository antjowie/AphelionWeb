#pragma once
#include "Core.hpp"
#include "Event/Event.hpp"

namespace ap {
/**
 * The engine runs systems.
 * At the moment systems runs synchroniously, but
 * in the future they will run concurrent. I have
 * yet to design how that will happen.
 *
 * Systems are updated and drawn in the order that they are pushed
 * Events are propogate in the opposite direction however. This allows us to
 * push a debug system that may want to intercept some events
 */
class APHELION_API System {
 public:
  virtual void Init(){};
  virtual void Deinit(){};
  virtual void Update(float ts){};
  virtual void Draw(){};
  virtual void Event(Event& event){};
};
}  // namespace ap