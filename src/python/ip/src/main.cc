/**
 * @file python/ip/src/main.cc
 * @date Tue Jan 18 17:07:26 2011 +0100
 * @author André Anjos <andre.anjos@idiap.ch>
 *
 * @brief Combines all modules to make up the complete bindings
 *
 * Copyright (C) 2011 Idiap Reasearch Institute, Martigny, Switzerland
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

#include "core/python/ndarray.h"

void bind_ip_version();
void bind_ip_ipcore();
void bind_ip_color();
void bind_ip_filters();
void bind_ip_block();
void bind_ip_crop_shift();
void bind_ip_extrapolate_mask();
void bind_ip_flipflop();
void bind_ip_gamma_correction();
void bind_ip_generate_with_center();
void bind_ip_integral();
void bind_ip_scale();
void bind_ip_shear();
void bind_ip_zigzag();
void bind_ip_rotate();
void bind_ip_flow();
void bind_ip_dctfeatures();
void bind_ip_gabor();
void bind_ip_gabor_wavelet_transform();
void bind_ip_geomnorm();
void bind_ip_faceeyesnorm();
void bind_ip_tantriggs();
void bind_ip_histogram();
void bind_ip_lbp_new();
void bind_ip_gaussian();
void bind_ip_median();
void bind_ip_drawing();
void bind_ip_spatiotempgrad();

#if defined(HAVE_VLFEAT)
void bind_ip_vlsift();
#endif

BOOST_PYTHON_MODULE(libpybob_ip) {

  bob::python::setup_python("bob image processing classes and sub-classes");

  bind_ip_version();
  bind_ip_ipcore();
  bind_ip_color();
  bind_ip_filters();
  bind_ip_block();
  bind_ip_crop_shift();
  bind_ip_extrapolate_mask();
  bind_ip_flipflop();
  bind_ip_gamma_correction();
  bind_ip_generate_with_center();
  bind_ip_integral();
  bind_ip_scale();
  bind_ip_shear();
  bind_ip_zigzag();
  bind_ip_rotate();
  bind_ip_flow();
  bind_ip_dctfeatures();
  bind_ip_gabor();
  bind_ip_gabor_wavelet_transform();
  bind_ip_geomnorm();
  bind_ip_faceeyesnorm();
  bind_ip_tantriggs();
  bind_ip_histogram();
  bind_ip_lbp_new();
  bind_ip_gaussian();
  bind_ip_median();
  bind_ip_drawing();
  bind_ip_spatiotempgrad();
#if defined(HAVE_VLFEAT)
  bind_ip_vlsift();
#endif
}
