// VolEsti (volume computation and sampling library)

// Copyright (c) 2018 Vissarion Fisikopoulos, Apostolos Chalkis

//Contributed and/or modified by Apostolos Chalkis, as part of Google Summer of Code 2018 program.

// VolEsti is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
//
// VolEsti is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.
//
// See the file COPYING.LESSER for the text of the GNU Lesser General
// Public License.  If you did not receive this file along with HeaDDaCHe,
// see <http://www.gnu.org/licenses/>.


#ifndef SAMPLE_ONLY_H
#define SAMPLE_ONLY_H

template <class T, class K, typename FT>
void sampling_only(K &randPoints, T &P, int walk_len, int rnum, bool gaussian, FT a, Point internal_point, vars var1, vars_g var2) {

    bool print = var1.verbose;
    int n = var1.n;
    Point p = internal_point;
    if(print) std::cout<<"\ncomputing first random point..."<<std::endl;
    Point q = get_point_on_Dsphere(n, var1.che_rad);
    p=p+q;
    rand_point_generator(P, p, 1, 50 * n, randPoints, var1);

    if(print) std::cout<<"\nfirst random point computed!"<<std::endl;
    if(print) std::cout<<"p = ";
    if(print) p.print();

    randPoints.clear();
    if(print) std::cout<<"\nsampling points..."<<std::endl;
    if (!gaussian){
        rand_point_generator(P, p, rnum, walk_len, randPoints, var1);
    } else {
        rand_gaussian_point_generator(P, p, rnum, walk_len, randPoints, a, var2);
    }
    if(print) std::cout<<"\nsampling completed!\n"<<std::endl;

}

#endif