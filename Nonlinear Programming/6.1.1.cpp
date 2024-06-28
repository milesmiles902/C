Question 6.1.1:

Function: f(x1,x2) = x1

Constraint: |x1| + |x2| <= 1
  
            g(x1,x2) = 1 - |x1| - |x2|

Set of Optimal Solutions: S = { x | for some x in S, mu1*f(x1,x2) + mu2*g(x1,x2) = c}
                            
                            = { x | for some x in S, mu1*x1 + mu2*(1-|x1|-|x2|) = c}

Geometric Multiplier:     1) Lagrangian: L(x1,x2,mu,lambda) = mu1*x1+mu2*(1-|x1|-|x2|)
 
                          2) Lagrangian Minimum: dL(x1,x2,mu1,mu2)/dx1 = mu1-mu2;

                                                                        = 0 
 
                                                 dL(x1,x2,mu1,mu2)/dx2 = -mu2

                                                                        = 0

                                                 dL(x1,x2,mu1,mu2)/dmu1 = x1

                                                                        = 0

                                                 dL(x1,x2,mu1,mu2)/dmu2 = 1-|x1|-|x2|

                                                                        = 0

                                                      (x1*,x2*,mu1,mu2) = (0, (+/-)1, 0, 0)

Plot: ...finish.

Function: f(x1,x2) = x1

Constraint: |x1| + |x2| <= 1

            g(x1,x2) = 1 - |x1| - |x2|

            where |x1| <= 1, and |x2| <= 1

Set of Optimal Solutions: S = { x | for some x in S, mu1*f(x1,x2) + mu2*g(x1,x2) + mu3*(1-|x1|) + mu4*(1-|x2|) = c}

Geometric Multiplier:     1) Lagrangian: L(x1,x2,mu1,mu2,mu3,mu4) = mu1*x1 + mu2*(1-|x1|-|x2|) + mu3*(1-|x1|) + mu4*(1-|x2|);

                          2) Lagrangian Minimum: dL(x1,x2,mu1,mu2,mu3,mu4)/dx1 = mu1-mu2-mu3;

                                                                         = 0

                                                 dL(x1,x2,mu,lambda)/dx2 = -mu2-mu4

                                                                         = 0

                                                dL(x1,x2,mu,lambda)/dmu1 = x1

                                                                         = 0

                                                dL(x1,x2,mu,lambda)/dmu2 = (1-|x1|-|x2|)

                                                                         = 0
  
                                                dL(x1,x2,mu,lambda)/dmu3 = (1-|x1|)

                                                                         = 0

                                                dL(x1,x2,mu,lambda)/dmu4 = (1-|x2|)

                                                                         = 0

                                               (x1*,x2*,mu1,mu2,mu3,mu4) = (0, (+/-)1, 1, 1, 0 , -1), (0, (+/-)1, -1, -1, 0 , 1)

Plot: ...finish.

Rules: Definition 5.1.1:
         For a vector mu = (mu1, mu2, ... , muR}
         A geometric multiplier vector exists in a primal dual problem, mu > 0
         At the Lagrangian minimum, f* = infL(x,mu*)
