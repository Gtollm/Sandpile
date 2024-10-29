#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <iterator>
#include <utility>

#include "lib/bmp_writer/bmp.hpp"
#include "lib/linked_list/linked_list.hpp"
#include "lib/matrix/matrix.hpp"
#include "sandpile.hpp"

const char* kFileName = "stage";
constexpr int kSpecialLength = 5;

Sandpile::Sandpile() {}
Sandpile::Sandpile(BmpWriter* writer) : writer_(writer) {}
Sandpile::~Sandpile() {}

utils::Matrix<uint64_t>& Sandpile::GetMatrix() { return this->matrix_; }

const utils::Matrix<uint64_t>& Sandpile::GetMatrix() const {
  return this->matrix_;
}

void Sandpile::SetPoint(std::int16_t ux, std::int16_t uy,
                        std::uint64_t val) {
  if (this->matrix_.GetXNormalized(ux) < 0) {
    this->matrix_.Extend(utils::Direction::LEFT,
                         std::abs(this->matrix_.GetXNormalized(ux)));
  }
  if (this->matrix_.GetYNormalized(uy) < 0) {
    this->matrix_.Extend(utils::Direction::UP,
                         std::abs(this->matrix_.GetYNormalized(uy)));
  }
  if (this->matrix_.GetYNormalized(uy) >= this->matrix_.GetHeight()) {
    this->matrix_.Extend(
        utils::Direction::DOWN,
        this->matrix_.GetYNormalized(uy) - this->matrix_.GetHeight() + 1);
  }
  if (this->matrix_.GetXNormalized(ux) >= this->matrix_.GetWidth()) {
    this->matrix_.Extend(
        utils::Direction::RIGHT,
        this->matrix_.GetXNormalized(ux) - this->matrix_.GetWidth() + 1);
  }

  this->matrix_.SetUElement(uy, ux, val);
}

void Sandpile::SetPoint(UCoord coord, std::uint64_t val) {
  this->SetPoint(coord.ux, coord.uy, val);
}

void Sandpile::IncPoint(std::int16_t ux, std::int16_t uy, std::int16_t val) {
  std::int64_t curr = 0;
  if (this->matrix_.GetXNormalized(ux) >= 0 &&
      this->matrix_.GetYNormalized(uy) >= 0 &&
      this->matrix_.GetYNormalized(uy) < this->matrix_.GetHeight() &&
      this->matrix_.GetXNormalized(ux) < this->matrix_.GetWidth()) {
    curr = this->GetPoint(ux, uy);
  }
  this->SetPoint(ux, uy, curr + val);
}

void Sandpile::IncPoint(UCoord coord, std::int16_t val) {
  IncPoint(coord.ux, coord.uy, val);
}

void Sandpile::DecPoint(std::int16_t ux, std::int16_t uy, std::int16_t val) {
  std::int64_t curr = 0;
  if (this->matrix_.GetXNormalized(ux) >= 0 &&
      this->matrix_.GetYNormalized(uy) >= 0 &&
      this->matrix_.GetYNormalized(uy) < this->matrix_.GetHeight() &&
      this->matrix_.GetXNormalized(ux) < this->matrix_.GetWidth()) {
    curr = this->GetPoint(ux, uy);
  }
  this->SetPoint(ux, uy, curr - val);
}

void Sandpile::DecPoint(UCoord coord, std::int16_t val) {
  DecPoint(coord.ux, coord.uy, val);
}

std::uint64_t Sandpile::GetPoint(std::int16_t ux, std::int16_t uy) const {
  return this->matrix_[this->matrix_.GetYNormalized(uy)]
                      [this->matrix_.GetXNormalized(ux)];
}

std::uint64_t Sandpile::GetPoint(UCoord coord) const {
  return this->GetPoint(coord.ux, coord.uy);
}

void Sandpile::AddToUnsteady(std::int16_t ux, std::int16_t uy) {
  this->unsteady_.push_back({ux, uy});
}

void Sandpile::AddToUnsteady(UCoord coord) {
  AddToUnsteady(coord.ux, coord.uy);
}

Sandpile::UCoord Sandpile::PopFromUnsteady(std::int16_t ux,
                                           std::int16_t uy) {
  return this->unsteady_.pop_front();
}

Sandpile::UCoord Sandpile::PopFromUnsteady(UCoord coord) {
  return PopFromUnsteady(coord.ux, coord.uy);
}

void Sandpile::AddIfUnsteady(std::int16_t ux, std::int16_t uy) {
  if (this->GetPoint(ux, uy) >= 4 &&
      this->unsteady_.Search({ux, uy}) == nullptr) {
    this->unsteady_.push_back({ux, uy});
  }
}

void Sandpile::AddIfUnsteady(UCoord coord) {
  AddIfUnsteady(coord.ux, coord.uy);
}

void Sandpile::Scatter(uint64_t max_iter, uint64_t frequency) {
  std::size_t i = 0;
  this->writer_->CreateDir();
  char* path;
  while (this->Iterate() && i < max_iter) {
    path = this->writer_->GetPath(kFileName, i);
    if (frequency != 0 && i % frequency == 1) {
      this->writer_->WriteBmp(path, this->matrix_);
    }
    ++i;
    delete[] path;
  }
  path = this->writer_->GetPath(kFileName, -1);
  this->writer_->WriteBmp(path, this->matrix_);
  delete[] path;
}

bool Sandpile::Iterate() {
  bool changed = false;
  std::size_t length = this->unsteady_.Size();
  for (std::size_t i = 0; i < length; ++i) {
    UCoord it = this->unsteady_.pop_back();
    if (this->GetPoint(it.ux, it.uy) >= 4) {
      this->DecPoint(it.ux, it.uy, 4);
      this->AddIfUnsteady(it);
      changed = true;
      IncPoint(it.ux + 1, it.uy);
      this->AddIfUnsteady(it.ux + 1, it.uy);
      IncPoint(it.ux - 1, it.uy);
      this->AddIfUnsteady(it.ux - 1, it.uy);
      IncPoint(it.ux, it.uy + 1);
      this->AddIfUnsteady(it.ux, it.uy + 1);
      IncPoint(it.ux, it.uy - 1);
      this->AddIfUnsteady(it.ux, it.uy - 1);
    }
  }

  return changed;
}

Sandpile::UCoord& Sandpile::UCoord::operator=(const UCoord& obj) {
  this->ux = obj.ux;
  this->uy = obj.uy;
  return *this;
}

bool Sandpile::UCoord::operator==(const UCoord& other) const {
  return (this->ux == other.ux && this->uy == other.uy);
}

bool Sandpile::UCoord::operator!=(const UCoord& other) const {
  return (*this) != other;
}
