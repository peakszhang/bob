/**
 * @file sp/cxx/FFT2DKiss.cc
 * @date Wed Apr 13 23:08:13 2011 +0200
 * @author Laurent El Shafey <Laurent.El-Shafey@idiap.ch>
 *
 * @brief Implement a naive 2D Fast Fourier Transform
 *
 * Copyright (C) 2011-2013 Idiap Research Institute, Martigny, Switzerland
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <bob/sp/FFT2DKiss.h>
#include <bob/core/assert.h>

bob::sp::FFT2DKissAbstract::FFT2DKissAbstract(
    const size_t height, const size_t width):
  m_height(height), m_width(width),
  m_buffer_hw(height, width), m_buffer_h(height),
  m_buffer_h2(height)
{
}

bob::sp::FFT2DKissAbstract::FFT2DKissAbstract(
    const bob::sp::FFT2DKissAbstract& other):
  m_height(other.m_height), m_width(other.m_width),
  m_buffer_hw(other.m_height, other.m_width), m_buffer_h(other.m_height),
  m_buffer_h2(other.m_height)
{
}

bob::sp::FFT2DKissAbstract::~FFT2DKissAbstract()
{
}

bob::sp::FFT2DKissAbstract& 
bob::sp::FFT2DKissAbstract::operator=(const FFT2DKissAbstract& other)
{
  if (this != &other) {
    setHeight(other.m_height);
    setWidth(other.m_width);
    m_buffer_hw.resize(other.m_height, other.m_width);
    m_buffer_h.resize(other.m_height);
    m_buffer_h2.resize(other.m_height);
  }
  return *this;
}

bool bob::sp::FFT2DKissAbstract::operator==(const bob::sp::FFT2DKissAbstract& b) const
{
  return (this->m_height == b.m_height && this->m_width == b.m_width);
}

bool bob::sp::FFT2DKissAbstract::operator!=(const bob::sp::FFT2DKissAbstract& b) const
{
  return !(this->operator==(b));
}

void bob::sp::FFT2DKissAbstract::operator()(const blitz::Array<std::complex<double>,2>& src, 
  blitz::Array<std::complex<double>,2>& dst) const
{
  // Check input, inclusive dimension
  bob::core::array::assertZeroBase(src);
  const blitz::TinyVector<int,2> shape(m_height,m_width);
  bob::core::array::assertSameShape(src, shape);

  // Check output
  bob::core::array::assertCZeroBaseContiguous(dst);
  bob::core::array::assertSameShape(dst, src);

  // Process
  processNoCheck(src, dst);
}

void bob::sp::FFT2DKissAbstract::setHeight(const size_t height)
{
  m_height = height;
  m_buffer_hw.resize(m_height, m_width);
  m_buffer_h.resize(m_height);
  m_buffer_h2.resize(m_height);
}

void bob::sp::FFT2DKissAbstract::setWidth(const size_t width)
{
  m_width = width;
  m_buffer_hw.resize(m_height, m_width);
  m_buffer_h.resize(m_height);
  m_buffer_h2.resize(m_height);
}
 

bob::sp::FFT2DKiss::FFT2DKiss(const size_t height, const size_t width):
  bob::sp::FFT2DKissAbstract::FFT2DKissAbstract(height, width),
  m_fft_h(height),
  m_fft_w(width)
{
}

bob::sp::FFT2DKiss::FFT2DKiss(const bob::sp::FFT2DKiss& other):
  bob::sp::FFT2DKissAbstract(other),
  m_fft_h(other.m_height),
  m_fft_w(other.m_width)
{
}

bob::sp::FFT2DKiss::~FFT2DKiss()
{
}

bob::sp::FFT2DKiss& 
bob::sp::FFT2DKiss::operator=(const FFT2DKiss& other)
{
  if (this != &other) {
    bob::sp::FFT2DKissAbstract::operator=(other);
    m_fft_h.setLength(other.m_height);
    m_fft_w.setLength(other.m_width);
  }
  return *this;
}

void bob::sp::FFT2DKiss::setHeight(const size_t height)
{
  bob::sp::FFT2DKissAbstract::setHeight(height);
  m_fft_h.setLength(height);
}

void bob::sp::FFT2DKiss::setWidth(const size_t width)
{
  bob::sp::FFT2DKissAbstract::setWidth(width);
  m_fft_w.setLength(width);
}
 
void bob::sp::FFT2DKiss::processNoCheck(const blitz::Array<std::complex<double>,2>& src, 
  blitz::Array<std::complex<double>,2>& dst) const
{
  blitz::Range rall = blitz::Range::all();
  // Compute the FFT
  for (int i=0; i<(int)m_height; ++i) {
    const blitz::Array<std::complex<double>,1> srci = src(i, rall);
    blitz::Array<std::complex<double>,1> bufi = m_buffer_hw(i, rall);
    m_fft_w(srci, bufi);
  }
  for (int j=0; j<(int)m_width; ++j) {
    m_buffer_h = m_buffer_hw(rall, j);
    m_fft_h(m_buffer_h, m_buffer_h2);
    blitz::Array<std::complex<double>,1> dstj = dst(rall, j);
    dstj = m_buffer_h2;
  }
}


bob::sp::IFFT2DKiss::IFFT2DKiss(const size_t height, const size_t width):
  bob::sp::FFT2DKissAbstract::FFT2DKissAbstract(height, width),
  m_ifft_h(height),
  m_ifft_w(width)
{
}

bob::sp::IFFT2DKiss::IFFT2DKiss(const bob::sp::IFFT2DKiss& other):
  bob::sp::FFT2DKissAbstract(other),
  m_ifft_h(other.m_height),
  m_ifft_w(other.m_width)
{
}

bob::sp::IFFT2DKiss::~IFFT2DKiss()
{
}

bob::sp::IFFT2DKiss& 
bob::sp::IFFT2DKiss::operator=(const IFFT2DKiss& other)
{
  if (this != &other) {
    bob::sp::FFT2DKissAbstract::operator=(other);
    m_ifft_h.setLength(other.m_height);
    m_ifft_w.setLength(other.m_width);
  }
  return *this;
}

void bob::sp::IFFT2DKiss::setHeight(const size_t height)
{
  bob::sp::FFT2DKissAbstract::setHeight(height);
  m_ifft_h.setLength(height);
}

void bob::sp::IFFT2DKiss::setWidth(const size_t width)
{
  bob::sp::FFT2DKissAbstract::setWidth(width);
  m_ifft_w.setLength(width);
}

void bob::sp::IFFT2DKiss::processNoCheck(const blitz::Array<std::complex<double>,2>& src, 
  blitz::Array<std::complex<double>,2>& dst) const
{
  blitz::Range rall = blitz::Range::all();
  // Compute the FFT
  for (int i=0; i<(int)m_height; ++i) {
    const blitz::Array<std::complex<double>,1> srci = src(i, rall);
    blitz::Array<std::complex<double>,1> bufi = m_buffer_hw(i, rall);
    m_ifft_w(srci, bufi);
  }
  for (int j=0; j<(int)m_width; ++j) {
    m_buffer_h = m_buffer_hw(rall, j);
    m_ifft_h(m_buffer_h, m_buffer_h2);
    blitz::Array<std::complex<double>,1> dstj = dst(rall, j);
    dstj = m_buffer_h2;
  }
}
