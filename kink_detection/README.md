
Problem: Kinks are not welcome.

base idea: So, can we detect them in fits automatically, and determine the fit presenting the least kinks in highly correlated and complex set of fits? Properties like differentials (parametric property) and curvature (geometric property) can be used for this effect. These. can the fit be made to minimise these values in order to get a fit with better form than can be achieved simply by using errors and residuals?

idea: for higher dimensions than 2D, can advances in spline detection etc. be applied to minimise error or correct form while fitting.


When curve fitting complex equations using complex algorithms, kinks may appear in the final curve. Usually a visual inspection done by the user is required to accept or reject the fit if it is scientifically innacurate and does not reproduce correct natural behaviour (here, due to the presence of a kink). This document aims to provide a more automated and accurate method for detecting and rejecting fits presenting kinks.

Below is a simple example of a curve fit to which a kink is manually introduced to simply introduce the problem and solution to exclude "bad fits" is proposed.

Author Note: The problem presented is derived from a real problem encountered during the fitting of ReaxFF Force Fields in Reactive Molecular Dynamics. The work ended up being unpublished due to various reasons. I did not want to let the idea simply die on an internal cloud server somewhere as I couldn't find this technique applied in published works or programs I know. Most solutions address the numerical value deviation from reference data, not the geometric shape/geometric continuity of the fitted curve.

proposed solution:
Difference quotient
Menger Curvature
