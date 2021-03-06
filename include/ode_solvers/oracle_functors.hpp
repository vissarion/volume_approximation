// VolEsti (volume computation and sampling library)

// Copyright (c) 2012-2020 Vissarion Fisikopoulos
// Copyright (c) 2018-2020 Apostolos Chalkis
// Copyright (c) 2020-2020 Marios Papachristou

// Contributed and/or modified by Marios Papachristou, as part of Google Summer of Code 2020 program.

// Licensed under GNU LGPL.3, see LICENCE file

#ifndef ORACLE_FUNCTORS_HPP
#define ORACLE_FUNCTORS_HPP

struct IsotropicQuadraticFunctor {

  // Holds function oracle and gradient oracle for the function 1/2 a ||x||^2
  template <
      typename NT
  >
  struct parameters {
    NT alpha;
    unsigned int order;
    NT L; // Lipschitz constant of gradient
    NT m; // Strong-convexity parameter
    NT kappa; // Condition number

    parameters() :
      alpha(NT(1)),
      order(2),
      L(NT(1)),
      m(NT(1)),
      kappa(1)
     {};

    parameters(
      NT alpha_,
      unsigned int order_) :
      alpha(alpha_),
      order(order_),
      L(alpha_),
      m(alpha_),
      kappa(1)
    {}
  };

  template
  <
      typename Point
  >
  struct GradientFunctor {
    typedef typename Point::FT NT;
    typedef std::vector<Point> pts;

    parameters<NT> &params;

    GradientFunctor(parameters<NT> &params_) : params(params_) {};

    // The index i represents the state vector index
    Point operator() (unsigned int const& i, pts const& xs, NT const& t) const {
      if (i == params.order - 1) {
        return (-params.alpha) * xs[0]; // returns - a*x
      } else {
        return xs[i + 1]; // returns derivative
      }
    }

  };

  template
  <
    typename Point
  >
  struct FunctionFunctor {
    typedef typename Point::FT NT;

    parameters<NT> &params;

    FunctionFunctor(parameters<NT> &params_) : params(params_) {};

    NT operator() (Point const& x) const {
      return 0.5 * params.alpha * x.dot(x);
    }

  };

};

struct IsotropicLinearFunctor {

  // Exponential Density
  template <
      typename NT
  >
  struct parameters {
    NT alpha;
    unsigned int order;
    NT L; // Lipschitz constant of gradient
    NT m; // Strong-convexity constant
    NT kappa; // Condition number

    parameters() :
      alpha(NT(1)),
      order(1),
      L(0),
      m(0),
      kappa(1)
     {};

    parameters(NT alpha_, unsigned int order_) :
      alpha(alpha_),
      order(order),
      L(0),
      m(0),
      kappa(1)
    {}
  };

  template
  <
      typename Point
  >
  struct GradientFunctor {
    typedef typename Point::FT NT;
    typedef std::vector<Point> pts;

    parameters<NT> &params;

    GradientFunctor(parameters<NT> &params_) : params(params_) {};

    // The index i represents the state vector index
    Point operator() (unsigned int const& i, pts const& xs, NT const& t) const {
      if (i == params.order - 1) {
        Point y = Point::all_ones(xs[0].dimension());
        y = (- params.alpha) * y;
        return y;
      } else {
        return xs[i + 1]; // returns derivative
      }
    }

  };

  template
  <
    typename Point
  >
  struct FunctionFunctor {
    typedef typename Point::FT NT;

    parameters<NT> &params;

    FunctionFunctor(parameters<NT> &params_) : params(params_) {};

    NT operator() (Point const& x) const {
      return params.alpha * x.sum();
    }

  };

};

#endif
