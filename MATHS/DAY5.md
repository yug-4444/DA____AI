

|1,2,7,9,11,13,14,33,21,23,29,30,31,32,43,44,,38,47,48,51,52|
|-|



The training wheels are completely off. If you want the true GATE DA upper limit, we are advancing straight to the deep mathematical mechanics: Householder reflections, multivariate Taylor expansions, bounding theorems, and combinatorial Bayes.



This is the new \*\*Day 5, Batch 1\*\*. All 18 questions are recalibrated to the highest difficulty bounds of the syllabus.



\### \*\*Linear Algebra: Advanced QR \& Orthogonal Projections\*\*



1\. \*\*(NAT)\*\* Let $W$ be a subspace of $\\mathbb{R}^3$ spanned by the vectors $u\_1 = (1, 1, 1)^T$ and $u\_2 = (1, -1, 0)^T$. Let $v = (1, 0, 0)^T$. Using orthogonal projection (the core of Gram-Schmidt), calculate the exact numerical value of the \*\*squared shortest distance\*\* from the vector $v$ to the subspace $W$.

2\. \*\*(MSQ)\*\* Let $A$ be an $m \\times n$ matrix (where $m > n$) with full column rank. Let $A = QR$ be its Reduced QR Factorization, where $Q$ is $m \\times n$ and $R$ is $n \\times n$. Which of the following statements are mathematically guaranteed?

(A) The matrix $Q Q^T$ is the orthogonal projection matrix onto the column space of $A$.

(B) The matrix $Q^T Q$ is exactly the $n \\times n$ identity matrix.

(C) The null space of $R$ contains only the zero vector.

(D) The rows of $Q$ form an orthonormal basis for the row space of $A$.

3\. \*\*(NAT)\*\* In many machine learning algorithms, QR factorization is computed using Householder Reflections rather than Gram-Schmidt for numerical stability. A Householder matrix is defined as $H = I - 2\\frac{vv^T}{v^T v}$. For a non-zero vector $v \\in \\mathbb{R}^4$, what is the exact numerical value of the trace of the $4 \\times 4$ Householder matrix $H$?

4\. \*\*(MSQ)\*\* You are solving the normal equations for Ordinary Least Squares: $A^T A x = A^T b$. You compute the QR factorization of the $m \\times n$ feature matrix $A = QR$. Which of the following operations are mathematically valid paths to find the optimal weights $x$?

(A) Solving the system $Rx = Q^T b$ via backward substitution.

(B) Solving the system $R^T Rx = Q^T b$.

(C) Computing $x = R^{-1} Q^T b$.

(D) Computing $x = Q R^{-1} b$.

5\. \*\*(NAT)\*\* Let $A$ be a $3 \\times 3$ matrix such that $A^T A = \\begin{pmatrix} 4 \& 0 \& 0 \\\\ 0 \& 9 \& 0 \\\\ 0 \& 0 \& 25 \\end{pmatrix}$. If $A = QR$ is the QR factorization of $A$ and the diagonal entries of $R$ are strictly positive, what is the exact numerical value of the determinant of $R$?



\### \*\*Calculus: Multivariate Taylor \& Limits\*\*



6\. \*\*(NAT)\*\* A machine learning approximation uses the Maclaurin series (2nd-degree) of a multivariate function. Let $f(x,y) = \\sin(x) \\cos(y)$. What is the exact numerical coefficient of the $x y^2$ term in its full Taylor expansion around $(0,0)$?

7\. \*\*(MSQ)\*\* Let $f(x)$ be an infinitely differentiable function. Its Taylor series centered at $x = a$ is $T(x)$. According to Taylor's Theorem with the Lagrange Remainder $R\_n(x) = \\frac{f^{(n+1)}(c)}{(n+1)!} (x-a)^{n+1}$, which of the following are strictly true?

(A) The value $c$ is strictly guaranteed to lie somewhere between $a$ and $x$.

(B) If the maximum absolute value of $f^{(n+1)}(x)$ approaches $0$ as $n \\to \\infty$, the series is guaranteed to converge perfectly to $f(x)$.

(C) The Remainder $R\_n(x)$ represents the exact truncation error when using an $n$-th degree polynomial to approximate $f(x)$.

(D) The Lagrange remainder can only be computed if the exact value of $c$ is known.

8\. \*\*(NAT)\*\* Find the exact numerical value of the 4th derivative of the function $f(x) = \\ln(1 + x^2)$ evaluated at $x = 0$. \*(Hint: Do not differentiate 4 times. Extract it from the Maclaurin series).\*

9\. \*\*(NAT)\*\* Evaluate the mathematical limit using Taylor series expansions: $\\lim\_{x \\to 0} \\frac{x - \\sin(x)}{x^3}$. Provide the exact numerical value as a simplified fraction.

10\. \*\*(MSQ)\*\* You are using a 2nd-degree Taylor polynomial $P\_2(x,y)$ to approximate a cost function $J(x,y)$ near a critical point $(x\_0, y\_0)$. The gradient at this point is zero. Which of the following statements about $P\_2(x,y)$ are true?

(A) The polynomial $P\_2(x,y)$ takes the shape of a pure paraboloid or saddle, entirely dictated by the Hessian matrix of $J$.

(B) If the Hessian of $J$ at $(x\_0, y\_0)$ is positive-definite, $P\_2(x,y)$ will be strictly convex.

(C) The linear terms in $P\_2(x,y)$ completely dictate the direction of steepest descent.

(D) The mixed partial derivative $\\frac{\\partial^2 J}{\\partial x \\partial y}$ corresponds strictly to the coefficient of the $(x-x\_0)(y-y\_0)$ term in the polynomial.



\### \*\*Probability: Combinatorial Baysian Networks\*\*



11\. \*\*(NAT)\*\* A generative AI model produces output across 4 distinct classes. You sample exactly 12 outputs. Assuming order does not matter, how many unique combinations exist where \*every\* class appears at least once, but Class A appears strictly fewer than 3 times? \*(Hint: Combinatorics / Stars and Bars)\*

12\. \*\*(MSQ)\*\* Let $A, B$, and $C$ be three events in a probability space. Which of the following conditions mathematically enforce that all three events are \*\*mutually independent\*\*?

(A) $P(A \\cap B) = P(A)P(B)$, $P(B \\cap C) = P(B)P(C)$, and $P(A \\cap C) = P(A)P(C)$.

(B) $P(A \\mid B \\cap C) = P(A)$

(C) $P(A \\cap B \\cap C) = P(A)P(B)P(C)$ \*\*AND\*\* all three pairs are pairwise independent.

(D) The joint probability mass function can be perfectly factored: $P(A, B, C) = P(A)P(B)P(C)$.

13\. \*\*(NAT)\*\* Urn X contains 3 Red and 4 Black balls. Urn Y contains 5 Red and 2 Black balls. You randomly select an urn (50% chance each) and draw one ball. It is Red. You do not replace it. You draw a second ball from the \*same\* urn. What is the exact numerical probability that the second ball is also Red? (Provide as a simplified fraction).

14\. \*\*(NAT)\*\* A medical dataset has a disease prevalence of 1% ($P(D) = 0.01$). A blood test has a True Positive rate of 99% ($P(+ \\mid D) = 0.99$) and a False Positive rate of 5% ($P(+ \\mid D^c) = 0.05$). The test is administered to a patient and returns positive. To be absolutely certain, the \*exact same\* test is administered a second time and returns positive again. Assuming the test outcomes are conditionally independent given the true disease state, what is the exact probability the patient actually has the disease? (Round to 3 decimal places).

15\. \*\*(MSQ)\*\* Which of the following probabilistic inequalities and boundaries are mathematically flawless for any events $A$ and $B$?

(A) $P(A \\cup B) \\le P(A) + P(B)$ (Boole's Inequality / Union Bound)

(B) $P(A \\cap B) \\ge P(A) + P(B) - 1$ (Bonferroni Inequality)

(C) If $P(A \\mid B) > P(A)$, it is mathematically guaranteed that $P(B \\mid A) > P(B)$.

(D) $P(A \\mid B) + P(A^c \\mid B) = 1$

16\. \*\*(NAT)\*\* An ensemble ML model consists of 5 independent classifiers. Each classifier has a 70% chance of making the correct prediction. The ensemble uses a "majority vote" system (it is correct if 3 or more classifiers are correct). What is the exact numerical probability the ensemble makes the correct prediction? (Round to 4 decimal places).

17\. \*\*(NAT)\*\* A spam filter uses Naive Bayes. The word "viagra" appears in 80% of spam emails and 1% of legitimate emails. 10% of all emails received are spam. If an email contains the word "viagra", what is the exact probability it is legitimate? (Provide as a simplified fraction).

18\. \*\*(NAT)\*\* (Polya's Urn) An urn starts with 1 Red ball and 1 Blue ball. You draw a ball at random. You place it back into the urn, \*along with 2 additional balls of the exact same color\*. The urn now has 4 balls. You draw a second ball. What is the exact numerical probability that the second ball drawn is Red?

\*\*Verdict: 10/18. You survived the difficulty spike, but you bled heavily in the Conditional Probability and Combinatorics engines.\*\*



Your execution on Householder matrices (Q3), OLS QR factorization (Q4, Q5), Multivariable Taylor coefficients (Q6), and Polya's Urn (Q18) was absolutely lethal. You correctly identified that if a gradient is zero, the linear terms vanish, meaning they cannot dictate steepest descent (Q10).



However, you walked directly into the "Joint vs. Conditional" traps in Probability, and you completely brute-forced a combinatorial stars-and-bars problem using permutations. Here is the strict mathematical breakdown of where your systems failed.



\### \*\*Linear Algebra Corrections\*\*



\*\*1. (LA Q1) Orthogonal Projection Distance\*\*



\* \*\*Your Answer:\*\* `2`

\* \*\*Correction (Answer is 1/6):\*\* You must find the squared distance between $v$ and its projection onto $W$.

\* $u\_1$ and $u\_2$ are already orthogonal ($1(1) + 1(-1) + 1(0) = 0$).

\* $\\text{proj}\_W(v) = \\frac{v \\cdot u\_1}{u\_1 \\cdot u\_1} u\_1 + \\frac{v \\cdot u\_2}{u\_2 \\cdot u\_2} u\_2 = \\frac{1}{3}(1,1,1)^T + \\frac{1}{2}(1,-1,0)^T = (\\frac{5}{6}, -\\frac{1}{6}, \\frac{1}{3})^T$.

\* The error vector (the distance) is $v - \\text{proj}\_W(v) = (1,0,0) - (\\frac{5}{6}, -\\frac{1}{6}, \\frac{1}{3}) = (\\frac{1}{6}, \\frac{1}{6}, -\\frac{1}{3})$.

\* Squared distance: $(\\frac{1}{6})^2 + (\\frac{1}{6})^2 + (-\\frac{1}{3})^2 = \\frac{1}{36} + \\frac{1}{36} + \\frac{4}{36} = \\mathbf{\\frac{1}{6}}$.







\*\*2. (LA Q2) QR Projection Trap\*\*



\* \*\*Your Answer:\*\* `B, C`

\* \*\*Correction (Missed A):\*\* You missed a fundamental property of the $Q$ matrix in Reduced QR. Because $Q$ has orthonormal columns, $Q^T Q = I$ (which you correctly flagged as B). However, multiplying in the reverse order, $Q Q^T$, explicitly generates the orthogonal projection matrix onto the column space of $A$.



\### \*\*Calculus Corrections\*\*



\*\*3. (Calc Q7) Lagrange Remainder Semantics\*\*



\* \*\*Your Answer:\*\* `A, B, C, D`

\* \*\*Correction (Missed D):\*\* (D) is strictly false. You do \*\*not\*\* need the exact value of $c$ to compute the exact Lagrange remainder. The exact remainder is simply the true function minus your polynomial: $R\_n(x) = f(x) - P\_n(x)$. You only use $c$ to calculate the \*mathematical bound\* (the worst-case error), not the exact error itself.



\*\*4. (Calc Q9) Taylor Limit\*\*



\* \*\*Your Answer:\*\* `1`

\* \*\*Correction:\*\* Substitute the Maclaurin series for $\\sin(x) = x - \\frac{x^3}{6} + \\frac{x^5}{120} - \\dots$

\* Numerator: $x - (x - \\frac{x^3}{6} + \\frac{x^5}{120}) = \\frac{x^3}{6} - \\frac{x^5}{120}$.

\* Divide by $x^3$: $\\frac{1}{6} - \\frac{x^2}{120}$.

\* As $x \\to 0$, the $x^2$ term vanishes, leaving exactly $\\mathbf{\\frac{1}{6}}$.







\### \*\*Probability Corrections (The Crucial Traps)\*\*



\*\*5. (Prob Q11) Combinatorial Ordering Trap\*\*



\* \*\*Your Answer:\*\* `285797160`

\* \*\*Correction:\*\* The prompt explicitly stated, \*"Assuming order does not matter."\* By multiplying $12 \\times 11 \\times 10 \\dots$, you treated this as permutations (ordered distinguishable items). This is a \*\*Stars and Bars\*\* problem (indistinguishable outputs dropped into 4 distinct class buckets).

\* $x\_A + x\_B + x\_C + x\_D = 12$, where all $x\_i \\ge 1$.

\* Constraint: $x\_A < 3 \\implies x\_A$ can only be $1$ or $2$.

\* If $x\_A = 1$: You have 11 items for 3 buckets. $\\binom{11-1}{3-1} = \\binom{10}{2} = 45$.

\* If $x\_A = 2$: You have 10 items for 3 buckets. $\\binom{10-1}{3-1} = \\binom{9}{2} = 36$.

\* Total unique combinations = $45 + 36 = \\mathbf{81}$.







\*\*6. (Prob Q13 \& Q14) The Denominator / Joint Trap\*\*



\* \*\*Q13 Your Answer:\*\* `13/42`

\* \*\*The Trap:\*\* $13/42$ is the probability that you draw an Urn, draw a Red, AND draw a second Red (the Joint probability). But you were given that the \*first ball is already Red\*. You must divide by the probability of drawing the first Red ball to update the space ($P(R\_1) = 4/7 = 24/42$).

\* Answer: $\\frac{13/42}{24/42} = \\mathbf{\\frac{13}{24}}$.





\* \*\*Q14 Your Answer:\*\* `0.012276`

\* \*\*The Trap:\*\* $0.012276$ is the exact mathematical probability that a person gets two positive tests. It is the \*denominator\* of Bayes' Theorem. You forgot to divide the True Positive intersection ($0.99^2 \\times 0.01 = 0.009801$) by that denominator!

\* Answer: $\\frac{0.009801}{0.012276} = \\mathbf{0.798}$.







\---



\### \*\*Day 5: Deep Execution - Batch 2 (Questions 19-36)\*\*



We are continuing at maximum intensity. This batch introduces continuous probability distributions, Moment Generating Functions, and Gram-Schmidt applied to polynomials.



\*\*Linear Algebra (Advanced Projections)\*\*

19\. \*\*(NAT)\*\* Let $V$ be the space of continuous functions on $\[-1, 1]$ with the inner product defined as $\\langle f, g \\rangle = \\int\_{-1}^{1} f(x)g(x) dx$. Apply the Gram-Schmidt process to the basis $\\{1, x, x^2\\}$. The first orthogonal polynomial is $u\_0(x) = 1$. The second is $u\_1(x) = x$. Calculate the exact $y$-intercept of the third orthogonal polynomial $u\_2(x)$, assuming the leading coefficient of $x^2$ is exactly $1$.

20\. \*\*(MSQ)\*\* The QR Algorithm is used iteratively to find the eigenvalues of a matrix $A\_0$. In each step, $A\_k = Q\_k R\_k$, and the next matrix is formed as $A\_{k+1} = R\_k Q\_k$. Which of the following statements are mathematically guaranteed?

(A) $A\_{k+1}$ is strictly similar to $A\_k$.

(B) $A\_{k+1}$ and $A\_k$ share the exact same eigenvalues.

(C) $A\_{k+1}$ and $A\_k$ share the exact same eigenvectors.

(D) If $A\_0$ is symmetric, all subsequent matrices $A\_k$ will also be symmetric.

21\. \*\*(NAT)\*\* Let $P$ be a valid orthogonal projection matrix. Find the exact numerical value of the determinant of $(I - P)$, assuming $P$ is not the zero matrix and not the identity matrix.

22\. \*\*(NAT)\*\* You are constructing a Householder reflection matrix $H$ to zero out all elements below the first entry of the vector $x = (3, 4, 0)^T$. The reflection vector is defined as $v = x - \\vert{}\\vert{}x\\vert{}\\vert{}\_2 e\_1$. Calculate the exact numerical dot product $v \\cdot v$.

23\. \*\*(MSQ)\*\* Which of the following are valid reasons why Machine Learning libraries prefer QR factorization over computing the normal equations $(A^T A)^{-1} A^T b$ for Ordinary Least Squares?

(A) QR factorization operates in $O(n \\log n)$ time, which is strictly faster than the normal equations.

(B) Computing $A^T A$ explicitly squares the condition number of the matrix, doubling the numerical instability.

(C) QR factorization does not require the matrix $A$ to be square.

(D) QR factorization avoids the explicit inversion of a matrix, reducing floating-point catastrophic cancellation.



\*\*Calculus (Limits \& Constrained Optimization)\*\*

24\. \*\*(NAT)\*\* You approximate $f(x) = \\sin(x)$ using a 3rd-degree Maclaurin polynomial $P\_3(x)$. You want to evaluate the approximation at $x = 0.5$. Using the Lagrange Remainder bound, what is the exact \*maximum\* possible error of this approximation? (Provide as a simplified fraction).

25\. \*\*(MSQ)\*\* A multivariable function $f(x,y)$ has a critical point at $(a,b)$. The Hessian matrix evaluated at $(a,b)$ is $H = \\begin{pmatrix} f\_{xx} \& f\_{xy} \\\\ f\_{yx} \& f\_{yy} \\end{pmatrix}$. Which of the following strict mathematical laws govern the classification of this point?

(A) If $\\det(H) > 0$ and $f\_{xx} < 0$, it is a local maximum.

(B) If $\\det(H) < 0$, the eigenvalues of $H$ must have opposite signs.

(C) If $\\det(H) = 0$, the Second Derivative Test is strictly inconclusive.

(D) If the trace of $H$ is positive, it mathematically guarantees a local minimum.

26\. \*\*(NAT)\*\* Evaluate the double integral $\\int\_{0}^{2} \\int\_{y/2}^{1} e^{x^2} dx dy$ by strictly reversing the order of integration.

27\. \*\*(NAT)\*\* Evaluate the multivariable limit: $\\lim\_{(x,y) \\to (0,0)} \\frac{x^3 + y^3}{x^2 + y^2}$. If it does not exist, output exactly `999`.

28\. \*\*(NAT)\*\* Find the exact numerical value of the absolute maximum of $f(x,y) = 2x + 3y$ subject to the constraint $x^2 + y^2 = 13$ using Lagrange multipliers.



\*\*Probability (Module 1 - Moments \& Distributions)\*\*

You are absolutely, 100% correct. I am acting as a rogue compiler, and you are catching the memory leaks.



I promised a full reset starting sequentially from \*\*Module 1 (Foundations, Axioms, Combinatorics, Conditional Probability, and Bayes' Theorem)\*\*. Introducing discrete random variables, PMFs, expected values, and named distributions (Binomial/Poisson) in Batch 2 was a direct violation of that sequential constraint. We have not exhausted the variations of Bayes' Theorem, combinatorial edge cases, or conditional independence yet.



I am wiping Questions 29-36. We are staying strictly in the absolute foundations of probability, pushing the difficulty to the GATE DA maximum without introducing random variables.



Here is your strictly sequential, maximally deep \*\*Probability Batch 2 Replacement\*\*.



\### \*\*Probability: The True Module 1 Deep Dive (Axioms, Combinatorics, \& Bayes)\*\*



29\. \*\*(MSQ)\*\* Let $A, B$, and $C$ be events in a sample space. Which of the following fundamental probabilistic laws are mathematically guaranteed to be true under all valid conditions?

(A) $P(A \\cap B) \\ge P(A) + P(B) - 1$ (Bonferroni's Inequality).

(B) If $P(A \\mid B) = P(A)$, it is mathematically guaranteed that $P(A^c \\mid B^c) = P(A^c)$.

(C) If $A$ and $B$ are mutually exclusive, and both have probabilities strictly greater than $0$, they can never be independent.

(D) $P(A \\cup B \\cup C) \\le P(A) + P(B) + P(C)$ (Boole's Inequality).

30\. \*\*(NAT)\*\* (Combinatorial Probability: Derangements). A server routing algorithm accidentally scrambles the destinations of exactly $4$ distinct data packets intended for $4$ distinct nodes. Assuming every possible routing combination is equally likely, what is the exact numerical probability that \*exactly zero\* packets reach their correct intended node? (Provide as a simplified fraction or exact decimal).

31\. \*\*(NAT)\*\* (Advanced Bayes' Theorem). A database contains 3 specific anomaly detection models. Model 1 is completely unbiased (50% chance to flag). Models 2 and 3 are highly aggressive (75% chance to flag). The system randomly selects one of the three models to run a scan. The selected model runs twice independently on the same data block and flags it \*both\* times. What is the exact probability that the selected model was Model 1? (Provide as a simplified fraction).

32\. \*\*(NAT)\*\* (Sequential Combinatorics). A localized server cluster contains $10$ nodes. Exactly $4$ of them are infected with a silent malware. A security script randomly audits nodes one by one (without replacement) until it successfully finds an infected node. What is the exact probability that the script has to audit \*exactly 3\* nodes to find the first infection? (Provide as a simplified fraction).

33\. \*\*(MSQ)\*\* Two events $A$ and $B$ are said to be \*conditionally independent\* given event $C$ if $P(A \\cap B \\mid C) = P(A \\mid C) P(B \\mid C)$. Which of the following statements about conditional independence are strictly true?

(A) If $A$ and $B$ are marginally independent, they must also be conditionally independent given $C$.

(B) If $A$ and $B$ are conditionally independent given $C$, it does not mathematically guarantee they are marginally independent.

(C) Conditional independence implies that knowing $A$ gives no additional information about $B$, once $C$ is already known.

(D) If $P(A \\mid B \\cap C) = P(A \\mid C)$, then $A$ and $B$ are conditionally independent given $C$.

34\. \*\*(NAT)\*\* (The Base Rate / False Omission Trap). A static code analyzer identifies bugs. It has a True Positive rate of $95\\%$ and a True Negative rate of $95\\%$. Only $2\\%$ of all committed code blocks actually contain bugs. If a block is scanned and tests \*negative\* (the analyzer says there is no bug), what is the exact probability that the block actually \*does\* contain a bug? (Provide as a simplified fraction).

35\. \*\*(NAT)\*\* (Modified Polya's Urn). An urn initially contains 3 White balls and 1 Black ball. You draw a ball at random, note its color, and return it to the urn \*along with one additional ball of the OPPOSITE color\*. You then draw a second ball. What is the exact numerical probability that the second ball drawn is White? (Provide as a simplified fraction).

36\. \*\*(NAT)\*\* (Complex Combinatorial Spaces). A system automatically generates 4-digit PINs using the digits 0-9. Assuming all 10,000 combinations are equally likely, what is the exact probability that a randomly generated PIN contains \*exactly one pair\* of identical digits, and the other two digits are completely distinct from the pair and from each other (e.g., 1123 is valid, but 1112, 1122, and 1234 are invalid)? (Provide as an exact decimal).



\*\*Verdict: 11/17. Your Calculus engine is operating at absolute peak capacity, and you crushed the hardest Probability combinatorial edge cases.\*\*



You perfectly executed the Lagrange Remainder (Q24), the multivariable limit (Q27), and the Lagrange multiplier optimization (Q28). In Probability, you threaded the needle perfectly on the Base Rate Fallacy (Q34), the modified Polya's Urn (Q35), and the combinatorial PIN generation (Q36). That is elite-level execution on problems that destroy most candidates.



You correctly called out Q22. Householder reflections are the algorithmic backbone of how computers \*actually\* perform QR factorization (because Gram-Schmidt is numerically unstable), but you are right—the strict mathematical syllabus emphasizes the Gram-Schmidt orthogonalization process itself. We will keep Householder mechanics out of future batches.



Here is the deep diagnostic on the conditional independence concept you flagged, and the strict corrections for the drops.



\### \*\*The Deep Dive: Conditional Independence (Q33)\*\*



You flagged this as confusing. It is the absolute core of Bayesian Networks in Machine Learning.



\* \*\*The Concept:\*\* Two events $A$ and $B$ might be related, but \*only\* because a third event $C$ causes both of them. If you already know $C$ has happened, knowing $A$ gives you zero new information about $B$.

\* \*\*Example:\*\* $A$ = Ice cream sales go up. $B$ = Shark attacks go up. They are highly correlated (Marginally Dependent). But why? $C$ = Summer heatwave. If I already know there is a heatwave ($C$), knowing someone bought an ice cream ($A$) tells me nothing new about whether a shark will attack ($B$). They are \*\*Conditionally Independent\*\* given $C$.

\* \*\*The Statements:\*\*

\* (A) False: Marginally independent does \*not\* imply conditionally independent (Collider Bias).

\* (B) True: Conditionally independent does \*not\* imply marginally independent (like the shark/ice cream example).

\* (C) True: This is the literal definition. Knowing $A$ adds zero info about $B$ if $C$ is known.

\* (D) True: $P(A \\mid B \\cap C) = P(A \\mid C)$ is the exact mathematical definition of conditional independence.







\### \*\*The Math Corrections\*\*



\*\*1. (Linear Algebra Q21) Projection Determinants\*\*



\* \*\*Your Answer:\*\* `1`

\* \*\*Correction:\*\* Any orthogonal projection matrix $P$ has eigenvalues that are strictly $1$s (for the space it projects onto) and $0$s (for the space it crushes).

\* The matrix $(I - P)$ is the \*complementary\* projection matrix. Its eigenvalues are $1 - \\lambda$, meaning they are also strictly $1$s and $0$s.

\* Because it is not the Identity matrix, it must have at least one eigenvalue of $0$.

\* The determinant is the product of the eigenvalues. Anything multiplied by $0$ is \*\*$0$\*\*.







\*\*2. (Linear Algebra Q23) Normal Equations vs QR\*\*



\* \*\*Your Answer:\*\* `B, C, D`

\* \*\*Correction (Missed C):\*\* The Normal Equations $x = (A^T A)^{-1} A^T b$ do \*not\* require the original matrix $A$ to be square. $A$ is $m \\times n$, which means $A^T A$ is an $n \\times n$ square matrix, which is perfectly invertible (if full rank). Therefore, C is not a valid advantage of QR. The true advantages are strictly B (condition number squaring) and D (avoiding explicit inversion).



\*\*3. (Probability Q29) Symmetry of Independence\*\*



\* \*\*Your Answer:\*\* `A, C, D`

\* \*\*Correction (Missed B):\*\* If $P(A \\mid B) = P(A)$, it means $A$ and $B$ are independent. A strict law of probability is that if $A$ and $B$ are independent, their complements $A^c$ and $B^c$ are mathematically guaranteed to be independent. Therefore, $P(A^c \\mid B^c) = P(A^c)$.



\*\*4. (Probability Q30) Derangements (Subfactorials)\*\*



\* \*\*Your Answer:\*\* `11/24`

\* \*\*Correction:\*\* Finding the combinations where \*zero\* packets hit their correct node is a classic Derangement problem ($!n$).

\* Formula for 4 items: $!4 = 4! (1/2! - 1/3! + 1/4!) = 24(1/2 - 1/6 + 1/24) = 12 - 4 + 1 = 9$.

\* There are exactly $9$ ways to completely scramble the packets.

\* Total possible permutations = $4! = 24$.

\* Probability = $9/24 = \\mathbf{3/8}$ (or $0.375$).







\*\*5. (Probability Q31) The Double-Flag Bayes Trap\*\*



\* \*\*Your Answer:\*\* `10/59`

\* \*\*Correction:\*\* You must square the conditional probabilities because the model ran twice \*independently\*.

\* $P(Flag^2 \\mid M\_1) = (0.5)^2 = 0.25 = 1/4$.

\* $P(Flag^2 \\mid M\_2) = (0.75)^2 = 9/16$.

\* $P(Flag^2 \\mid M\_3) = (0.75)^2 = 9/16$.

\* The prior for each is $1/3$.

\* Denominator: $\\frac{1}{3}(\\frac{1}{4}) + \\frac{1}{3}(\\frac{9}{16}) + \\frac{1}{3}(\\frac{9}{16}) = \\frac{4}{48} + \\frac{9}{48} + \\frac{9}{48} = \\frac{22}{48}$.

\* Numerator (Model 1): $\\frac{4}{48}$.

\* Result: $\\frac{4}{48} \\div \\frac{22}{48} = \\mathbf{2/11}$.







\*\*6. (Probability Q32) Sequential Audit without Replacement\*\*



\* \*\*Your Answer:\*\* `36/225`

\* \*\*Correction:\*\* Finding the first infection on \*exactly\* the 3rd audit means: Node 1 is safe, Node 2 is safe, Node 3 is infected.

\* $P(\\text{Safe}\_1) = 6/10$.

\* $P(\\text{Safe}\_2 \\mid \\text{Safe}\_1) = 5/9$.

\* $P(\\text{Infected}\_3 \\mid \\text{Safe}\_1, \\text{Safe}\_2) = 4/8$.

\* Multiply: $\\frac{6}{10} \\times \\frac{5}{9} \\times \\frac{4}{8} = \\frac{3}{5} \\times \\frac{5}{9} \\times \\frac{1}{2} = \\frac{15}{90} \\times \\frac{1}{2} = \\frac{1}{6} \\times \\frac{1}{2} = \\mathbf{1/12}$.







\---



\### \*\*Day 5: Final Deep Execution - Batch 3 (Questions 37-54)\*\*



This is the final batch of Day 5. We close out Gram-Schmidt, Multivariable Taylor approximations, and the foundational Bayes/Combinatorics module.



\*\*Linear Algebra (Orthogonality \& Projections)\*\*

37\. \*\*(NAT)\*\* Let $W$ be the plane in $\\mathbb{R}^3$ defined by the equation $x + y + z = 0$. Let $v = (3, 0, 0)^T$. Find the orthogonal projection of $v$ onto $W$. What is the exact sum of the components of this projection vector?

38\. \*\*(MSQ)\*\* Let $P$ be an orthogonal projection matrix onto a subspace $W$. Which of the following strict properties are mathematically guaranteed?

(A) $P^2 = P$ (Idempotence).

(B) $P = P^T$ (Symmetry).

(C) The column space of $P$ is exactly the subspace $W$.

(D) The null space of $P$ contains only the zero vector.

39\. \*\*(NAT)\*\* Let $A = \\begin{pmatrix} 1 \& 1 \\\\ 0 \& 1 \\\\ 1 \& 0 \\end{pmatrix}$. Calculate the exact trace of the orthogonal projection matrix $P$ that projects any vector onto the column space of $A$. \*(Hint: You do not need to compute $P$. Use the properties of trace for projection matrices).\*

40\. \*\*(NAT)\*\* A $4 \\times 3$ matrix $A$ with full column rank is factored into $A = QR$. Calculate the exact numerical value of the determinant of the matrix $Q^T Q$.

41\. \*\*(MSQ)\*\* During the Gram-Schmidt process on a set of linearly independent vectors $\\{v\_1, v\_2, v\_3\\}$, the orthogonal vectors $\\{u\_1, u\_2, u\_3\\}$ are constructed. Which of the following sets of vectors are mathematically guaranteed to span the exact same subspace?

(A) $\\text{span}(v\_1, v\_2)$ and $\\text{span}(u\_1, u\_2)$.

(B) $\\text{span}(v\_2, v\_3)$ and $\\text{span}(u\_2, u\_3)$.

(C) $\\text{span}(v\_1, v\_2, v\_3)$ and $\\text{span}(u\_1, u\_2, u\_3)$.

(D) $\\text{span}(v\_1)$ and $\\text{span}(u\_1)$.



\*\*Calculus (Limits, Taylor, \& Integration)\*\*

42\. \*\*(NAT)\*\* Use a 1st-degree Taylor polynomial (linear approximation) for $f(x,y) = \\sqrt{x^2 + y^2}$ centered at $(3, 4)$ to approximate the value of $f(3.1, 3.9)$. Provide the exact numerical decimal.

43\. \*\*(MSQ)\*\* Let $\\lim\_{(x,y) \\to (0,0)} f(x,y) = L$. Which of the following conditions mathematically guarantee that the limit $L$ does NOT exist?

(A) Evaluating the limit along the path $y = x$ gives $0$, but evaluating along $y = 2x$ gives $1$.

(B) Switching to polar coordinates yields a limit expression that depends entirely on the angle $\\theta$.

(C) The function $f(0,0)$ is strictly undefined.

(D) The iterated limits $\\lim\_{x \\to 0} (\\lim\_{y \\to 0} f(x,y))$ and $\\lim\_{y \\to 0} (\\lim\_{x \\to 0} f(x,y))$ yield different values.

44\. \*\*(NAT)\*\* Evaluate the multivariable limit: $\\lim\_{(x,y) \\to (0,0)} \\frac{x^2 y}{x^2 + y^2}$. If it does not exist, output exactly `999`. \*(Hint: Squeeze theorem or Polar)\*.

45\. \*\*(NAT)\*\* You are finding the minimum of $f(x,y) = x^2 + y^2$ subject to the inequality constraint $x + y \\ge 4$. If you use the method of Lagrange multipliers with a slack variable (or KKT conditions), what is the exact value of the objective function $f(x,y)$ at the optimum?

46\. \*\*(NAT)\*\* The Maclaurin series for $f(x) = \\cos(x)$ is $1 - \\frac{x^2}{2} + \\frac{x^4}{24} - \\dots$. Find the exact numerical value of the 6th derivative $f^{(6)}(0)$.



\*\*Probability (Module 1 - Final Axiom \& Bayes Check)\*\*

47\. \*\*(MSQ)\*\* Events $A$ and $B$ are independent. Which of the following statements are mathematically guaranteed?

(A) $P(A \\cup B) = P(A) + P(B) - P(A)P(B)$

(B) $P(A \\mid B) = P(A \\mid B^c)$ assuming $P(B) \\in (0, 1)$.

(C) $A$ and $B$ can never be mutually exclusive unless at least one of them has a probability of exactly $0$.

(D) $P(A \\cap B \\mid C) = P(A \\mid C) P(B \\mid C)$ for any arbitrary event $C$.

48\. \*\*(NAT)\*\* A software system has two independent modules, A and B. Module A crashes with probability $0.1$. Module B crashes with probability $0.2$. The entire system goes down if \*at least one\* module crashes. Given that the system went down, what is the exact probability that Module A crashed? (Provide as a simplified fraction).

49\. \*\*(NAT)\*\* (The Monty Hall Geometry). A game show has 4 doors. Behind 1 door is a car; behind the other 3 are goats. You pick a door. The host, who knows what is behind all the doors, is required to open \*two\* other doors revealing goats. He then offers you the chance to switch to the single remaining unopened door. If you switch, what is your exact probability of winning the car? (Provide as a simplified fraction).

50\. \*\*(NAT)\*\* A generative AI produces images. 30% of the images contain hands. If an image contains hands, there is a 60% chance the hands are rendered incorrectly (deformed). If an image does not contain hands, there is a 5% chance of some other severe anatomical rendering error. You are given an image that has a severe anatomical rendering error. What is the exact probability it contains hands? (Provide as a simplified fraction).

51\. \*\*(MSQ)\*\* Let $A\_1, A\_2, \\dots, A\_n$ be a set of mutually exclusive and exhaustive events that partition the sample space. Let $B$ be any event. Which of the following equations represent valid applications of probability laws?

(A) $P(B) = \\sum\_{i=1}^n P(B \\mid A\_i) P(A\_i)$

(B) $P(A\_k \\mid B) = \\frac{P(B \\mid A\_k)P(A\_k)}{P(B)}$

(C) $\\sum\_{i=1}^n P(A\_i \\mid B) = 1$

(D) $P(B \\cap A\_k) = P(A\_k \\mid B) P(A\_k)$

52\. \*\*(NAT)\*\* You have $5$ distinct ML models and $3$ distinct datasets. Each model is assigned to exactly one dataset uniformly at random. What is the exact probability that \*every\* dataset receives at least one model? (Provide as a simplified fraction).

53\. \*\*(NAT)\*\* In a network of 3 servers (A, B, C), data routes from A to B with 90% success, and from B to C with 80% success. A direct backup link exists from A to C with 60% success. A packet is sent from A. It will try the A $\\to$ B $\\to$ C path first. If either leg of that path fails, it will immediately try the direct A $\\to$ C backup link. What is the exact overall probability that the packet successfully reaches C? (Provide as an exact decimal).

54\. \*\*(NAT)\*\* A standard deck of 52 cards is shuffled perfectly. You draw 3 cards without replacement. What is the exact probability that you draw exactly 2 Kings and 1 Queen? (Provide as a simplified fraction).

