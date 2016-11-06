#include "material_manager.h"

namespace niepce
{

MaterialManager::MaterialManager()
{}

MaterialManager::~MaterialManager()
{}

auto MaterialManager::Size() const -> std::size_t
{
  return materials_.size();
}

auto MaterialManager::Find(const char* name) const -> Materials::const_iterator
{
  for (auto it = materials_.cbegin(); it != materials_.cend(); ++it)
  {
    if ((*it)->Name() == name)
    {
      return it;
    }
  }
  std::cerr << "Cannot Find " << name << "." << std::endl;
  return materials_.cbegin();
}

auto MaterialManager::Append(const std::shared_ptr<Material>& material) -> void
{
  materials_.push_back(material);
}

auto MaterialManager::Append(std::shared_ptr<Material>&& material) -> void
{
  materials_.push_back(std::move(material));
}

auto MaterialManager::Update(std::size_t idx, const std::shared_ptr<Material>& material) -> void
{
  if (idx >= Size())
  {
    std::cerr << "Cannot update material. Index out of range." << std::endl;
    return ;
  }
  materials_[idx] = material;
}

auto MaterialManager::Remove(const char* name) -> void
{
  Materials::const_iterator it = Find(name);
  materials_.erase(it);
}

auto MaterialManager::Remove(std::size_t idx) -> void
{
  if (idx >= Size())
  {
    std::cerr << "Cannot remove material. Index out of range." << std::endl;
    return ;
  }
  materials_.erase(materials_.cbegin() + idx);
}

auto MaterialManager::Clear() -> void
{
  materials_.clear();
}

} // namespace niepce
