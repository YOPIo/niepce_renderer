#ifndef _MATERIAL_MANAGER_H_
#define _MATERIAL_MANAGER_H_

#include <vector>
#include <memory>
#include <iostream>

#include "material.h"

namespace niepce
{

class MaterialManager
{
  using Materials = std::vector<std::shared_ptr<Material>>;

 public:
  MaterialManager();
  ~MaterialManager();

  MaterialManager(const MaterialManager& manager) = delete;
  MaterialManager(MaterialManager&& manager)      = delete;
  MaterialManager& operator = (const MaterialManager& manager) = delete;
  MaterialManager& operator = (MaterialManager&& manager)      = delete;

  /*
   * 現在のマテリアルの個数を返す
   */
  auto Size() const -> std::size_t;

  /*
   * 名前からマテリアルを探す
   * 存在　　　： idx
   * 存在しない： -1
   */
  auto Find(const char* name) const -> Materials::const_iterator;

  /*
   * マテリアルを追加
   */
  auto Append(const std::shared_ptr<Material>&  material) -> void;
  auto Append(std::shared_ptr<Material>&& material) -> void;

  /*
   * idx 番目のマテリアルを上書きする
   */
  auto Update(std::size_t idx, const std::shared_ptr<Material>& material) -> void;

  /*
   * マテリアルを削除
   * 成功；true
   * 失敗：false
   */
  auto Remove(const char* name) -> void;
  auto Remove(std::size_t idx)  -> void;

  /*
   * 全要素削除
   */
  auto Clear() -> void;

 private:
  Materials materials_;
};


} // namespace niepce


#endif // _MATERIAL_MANAGER_H_
