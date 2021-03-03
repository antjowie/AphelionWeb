#pragma once

#include <string>

#include "Aphelion/Core/Core.h"
#include "Aphelion/Renderer/Shader.h"

namespace ap {
class APHELION_API OpenGLShader : public Shader {
 public:
  OpenGLShader(const char* filepath);
  OpenGLShader(const char* name, const char* vertexSrc,
               const char* fragmentSrc);
  virtual ~OpenGLShader();

  virtual void Bind() const override final;
  virtual void Unbind() const override final;

  virtual void SetInt(const char* name, const int val) const override final;
  virtual void SetFloat(const char* name, const float val) const override final;
  virtual void SetBool(const char* name, const bool val) const override final;
  virtual void SetMat4(const char* name, const float* val) const override final;

  virtual void SetVec2(const char* name, const float* val) const override final;
  virtual void SetVec3(const char* name, const float* val) const override final;
  virtual void SetVec4(const char* name, const float* val) const override final;

 private:
  void Compile(const std::unordered_map<unsigned, std::string>& shaders);
  int GetUniformLocation(const char* name) const;

  unsigned m_id;
  std::string m_name;
};
}  // namespace ap