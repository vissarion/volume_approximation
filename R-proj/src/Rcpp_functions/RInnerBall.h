// VolEsti (volume computation and sampling library)

// Copyright (c) 20012-2018 Vissarion Fisikopoulos
// Copyright (c) 2018 Apostolos Chalkis

//Contributed and/or modified by Apostolos Chalkis, as part of Google Summer of Code 2018 program.

#ifndef RINNERBALL_H
#define RINNERBALL_H

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::export]]
Rcpp::NumericVector InnerBall(Rcpp::NumericMatrix A, bool Zono, bool Vpoly) {

    unsigned int m = A.nrow() - 1;
    unsigned int n = A.ncol() - 1;
    std::vector <std::vector<NT>> Pin(m + 1, std::vector<NT>(n + 1));

    for (unsigned int i = 0; i < m + 1; i++) {
        for (unsigned int j = 0; j < n + 1; j++) {
            Pin[i][j] = A(i, j);
        }
    }
    // construct polytope
    if (Zono) {
        ZP.init(Pin);
    } else if (!Vpoly) {
        HP.init(Pin);
    } else {
        VP.init(Pin);
    }

    std::pair <Point, NT> InnerBall;
    Rcpp::NumericVector vec(n + 1);
    if (Zono) {
        InnerBall = ZP.ComputeInnerBall();
    } else if (!Vpoly) {
        InnerBall = HP.ComputeInnerBall();
    } else {
        InnerBall = VP.ComputeInnerBall();
    }
    for (unsigned int k = 0; k < n; ++k) {
        vec(k) = InnerBall.first[k];
    }
    vec(n) = InnerBall.second;
    return vec;

}

#endif