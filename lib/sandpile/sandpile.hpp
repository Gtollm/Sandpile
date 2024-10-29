#pragma once

#include <cstdint>
#include <limits>

#include "lib/bmp_writer/bmp.hpp"
#include "lib/linked_list/linked_list.hpp"
#include "lib/matrix/matrix.hpp"

class Sandpile {
 private:
  struct UCoord {
    std::int16_t ux;
    std::int16_t uy;
    UCoord& operator=(const UCoord& obj);
    bool operator==(const UCoord& other) const;
    bool operator!=(const UCoord& other) const;
  };

 public:
  Sandpile();
  Sandpile(BmpWriter* writer);
  ~Sandpile();
  utils::Matrix<uint64_t>& GetMatrix();
  const utils::Matrix<uint64_t>& GetMatrix() const;
  void SetPoint(std::int16_t ux, std::int16_t uy, std::uint64_t val);
  void SetPoint(UCoord coord, std::uint64_t val);
  void IncPoint(std::int16_t ux, std::int16_t uy, std::int16_t val = 1);
  void IncPoint(UCoord coord, std::int16_t val = 1);
  void DecPoint(std::int16_t ux, std::int16_t uy, std::int16_t val = 1);
  void DecPoint(UCoord coord, std::int16_t val = 1);
  std::uint64_t GetPoint(std::int16_t ux, std::int16_t uy) const;
  std::uint64_t GetPoint(UCoord coord) const;
  void AddToUnsteady(std::int16_t ux, std::int16_t uy);
  void AddToUnsteady(UCoord coord);
  void AddIfUnsteady(std::int16_t ux, std::int16_t uy);
  void AddIfUnsteady(UCoord coord);
  UCoord PopFromUnsteady(std::int16_t ux, std::int16_t uy);
  UCoord PopFromUnsteady(UCoord coord);
  void Scatter(uint64_t max_iter = std::numeric_limits<uint64_t>::max(),
               uint64_t frequency = 0);
  bool Iterate();

 private:
  utils::Matrix<uint64_t> matrix_;
  utils::LinkedList<UCoord> unsteady_;

  BmpWriter* writer_;
};
