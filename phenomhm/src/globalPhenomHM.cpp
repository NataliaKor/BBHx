/*  This code was created by Michael Katz.
 *  It is shared under the GNU license (see below).
 *  Creates the structures that hold waveform and interpolation information
 *  for the CPU version of the PhenomHM waveform.
 *
 *
 *  Copyright (C) 2019 Michael Katz
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with with program; see the file COPYING. If not, write to the
 *  Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 */

 #include "globalPhenomHM.h"

 /*
 Function for creating ModeContainer on the cpu.
 */
ModeContainer * cpu_create_modes(int num_modes, int num_walkers, unsigned int *l_vals, unsigned int *m_vals, int max_length, int to_gpu, int to_interp){
        ModeContainer * mode_vals = new ModeContainer[num_modes*num_walkers];
        int i = 0;
        for (int j=0; j<num_walkers; j++){
            for (int k=0; k<num_modes; k++){
                i = j*num_modes + k;
                mode_vals[i].num_modes = num_modes;
                mode_vals[i].num_walkers = num_walkers;
                mode_vals[i].walker = j;
                mode_vals[i].l = l_vals[k];
                mode_vals[i].m = m_vals[k];
                mode_vals[i].max_length = max_length;
                mode_vals[i].to_gpu = to_gpu;
                mode_vals[i].to_interp = to_interp;

                if (mode_vals[i].to_gpu == 0){
                    mode_vals[i].amp = new double[max_length];
                    mode_vals[i].phase = new double[max_length];
                    mode_vals[i].freq_amp_phase = new double[max_length];
                    mode_vals[i].time_freq_corr = new double[max_length];

                    mode_vals[i].freq_response = new double[max_length];
                    mode_vals[i].phaseRdelay = new double[max_length];

                    mode_vals[i].transferL1_re = new double[max_length];
                    mode_vals[i].transferL1_im = new double[max_length];

                    mode_vals[i].transferL2_re = new double[max_length];
                    mode_vals[i].transferL2_im = new double[max_length];

                    mode_vals[i].transferL3_re = new double[max_length];
                    mode_vals[i].transferL3_im = new double[max_length];

                    if (mode_vals[i].to_interp == 1){
                        mode_vals[i].amp_coeff_1 = new double[max_length -1];
                        mode_vals[i].amp_coeff_2 = new double[max_length -1];
                        mode_vals[i].amp_coeff_3 = new double[max_length -1];
                        mode_vals[i].phase_coeff_1 = new double[max_length -1];
                        mode_vals[i].phase_coeff_2 = new double[max_length -1];
                        mode_vals[i].phase_coeff_3 = new double[max_length -1];

                        mode_vals[i].time_freq_coeff_1 = new double[max_length -1];
                        mode_vals[i].time_freq_coeff_2 = new double[max_length -1];
                        mode_vals[i].time_freq_coeff_3 = new double[max_length -1];

                        mode_vals[i].transferL1_re_coeff_1 = new double[max_length -1];
                        mode_vals[i].transferL1_re_coeff_2 = new double[max_length -1];
                        mode_vals[i].transferL1_re_coeff_3 = new double[max_length -1];
                        mode_vals[i].transferL1_im_coeff_1 = new double[max_length -1];
                        mode_vals[i].transferL1_im_coeff_2 = new double[max_length -1];
                        mode_vals[i].transferL1_im_coeff_3 = new double[max_length -1];

                        mode_vals[i].transferL2_re_coeff_1 = new double[max_length -1];
                        mode_vals[i].transferL2_re_coeff_2 = new double[max_length -1];
                        mode_vals[i].transferL2_re_coeff_3 = new double[max_length -1];
                        mode_vals[i].transferL2_im_coeff_1 = new double[max_length -1];
                        mode_vals[i].transferL2_im_coeff_2 = new double[max_length -1];
                        mode_vals[i].transferL2_im_coeff_3 = new double[max_length -1];

                        mode_vals[i].transferL3_re_coeff_1 = new double[max_length -1];
                        mode_vals[i].transferL3_re_coeff_2 = new double[max_length -1];
                        mode_vals[i].transferL3_re_coeff_3 = new double[max_length -1];
                        mode_vals[i].transferL3_im_coeff_1 = new double[max_length -1];
                        mode_vals[i].transferL3_im_coeff_2 = new double[max_length -1];
                        mode_vals[i].transferL3_im_coeff_3 = new double[max_length -1];

                        mode_vals[i].phaseRdelay_coeff_1 = new double[max_length -1];
                        mode_vals[i].phaseRdelay_coeff_2 = new double[max_length -1];
                        mode_vals[i].phaseRdelay_coeff_3 = new double[max_length -1];

                    }
                }
            }
        }
        return mode_vals;
}

/*
Destroy ModeContainer structures.
*/
void cpu_destroy_modes(ModeContainer * mode_vals){
    if (mode_vals[0].to_gpu == 0){
        for (int i=0; i<(mode_vals[0].num_modes*mode_vals[0].num_walkers); i++){
            delete[] mode_vals[i].amp;
            delete[] mode_vals[i].phase;
            delete[] mode_vals[i].freq_amp_phase;
            delete[] mode_vals[i].time_freq_corr;

            delete[] mode_vals[i].freq_response;
            delete[] mode_vals[i].phaseRdelay;

            delete[] mode_vals[i].transferL1_re;
            delete[] mode_vals[i].transferL1_im;

            delete[] mode_vals[i].transferL2_re;
            delete[] mode_vals[i].transferL2_im;

            delete[] mode_vals[i].transferL3_re;
            delete[] mode_vals[i].transferL3_im;

            if (mode_vals[i].to_interp == 1){
                delete[] mode_vals[i].amp_coeff_1;
                delete[] mode_vals[i].amp_coeff_2;
                delete[] mode_vals[i].amp_coeff_3;
                delete[] mode_vals[i].phase_coeff_1;
                delete[] mode_vals[i].phase_coeff_2;
                delete[] mode_vals[i].phase_coeff_3;
                delete[] mode_vals[i].time_freq_coeff_1;
                delete[] mode_vals[i].time_freq_coeff_2;
                delete[] mode_vals[i].time_freq_coeff_3;

                delete[] mode_vals[i].transferL1_re_coeff_1;
                delete[] mode_vals[i].transferL1_re_coeff_2;
                delete[] mode_vals[i].transferL1_re_coeff_3;
                delete[] mode_vals[i].transferL1_im_coeff_1;
                delete[] mode_vals[i].transferL1_im_coeff_2;
                delete[] mode_vals[i].transferL1_im_coeff_3;

                delete[] mode_vals[i].transferL2_re_coeff_1;
                delete[] mode_vals[i].transferL2_re_coeff_2;
                delete[] mode_vals[i].transferL2_re_coeff_3;
                delete[] mode_vals[i].transferL2_im_coeff_1;
                delete[] mode_vals[i].transferL2_im_coeff_2;
                delete[] mode_vals[i].transferL2_im_coeff_3;

                delete[] mode_vals[i].transferL3_re_coeff_1;
                delete[] mode_vals[i].transferL3_re_coeff_2;
                delete[] mode_vals[i].transferL3_re_coeff_3;
                delete[] mode_vals[i].transferL3_im_coeff_1;
                delete[] mode_vals[i].transferL3_im_coeff_2;
                delete[] mode_vals[i].transferL3_im_coeff_3;

                delete[] mode_vals[i].phaseRdelay_coeff_1;
                delete[] mode_vals[i].phaseRdelay_coeff_2;
                delete[] mode_vals[i].phaseRdelay_coeff_3;
            }
        }
    }
    delete[] mode_vals;
}
