\*\*Linear Algebra: Deep Execution (Day 1 Strict Scope)\*\*



1\. \*\*(NAT)\*\* Let $A$ be a $4 \\times 5$ real matrix and $B$ be a $5 \\times 4$ real matrix such that their product $AB = I\_4$, where $I\_4$ is the $4 \\times 4$ identity matrix. What is the exact dimension of the null space (nullity) of the $5 \\times 5$ matrix $C = BA$?

2\. \*\*(MSQ)\*\* Let $W\_1$ and $W\_2$ be two distinct $3$-dimensional subspaces of $\\mathbb{R}^5$. Which of the following are mathematically possible dimensions for the subspace $(W\_1 + W\_2)$?

(A) 3

(B) 4

(C) 5

(D) 6

3\. \*\*(NAT)\*\* Consider a non-homogeneous system of equations $Ax = b$ where $A$ is a $3 \\times 4$ matrix. The row-reduced echelon form (RREF) of $A$ has exactly two non-zero rows. If the system is known to be consistent, what is the exact dimension of the solution space?

4\. \*\*(MSQ)\*\* Let $V$ be the vector space of all $n \\times n$ real matrices. Let $W = \\{A \\in V \\mid A^T = A \\text{ and } A\_{11} + A\_{nn} = 0\\}$. Which of the following are true regarding the dimension of $W$?

(A) It is a valid subspace of $V$.

(B) For $n = 3$, the dimension of $W$ is $6$.

(C) For $n = 3$, the dimension of $W$ is $5$.

(D) The dimension is always $\\frac{n^2 + n - 2}{2}$.

5\. \*\*(NAT)\*\* Let $u, v, w$ be linearly independent vectors in $\\mathbb{R}^3$. Find the exact rank of the $3 \\times 3$ matrix $M$ formed by the outer products: $M = uv^T + vw^T + wu^T$. \*(Hint: Consider the column space of M).\*

6\. \*\*(MSQ)\*\* Let $A$ be an $m \\times n$ matrix with $m < n$. Which of the following statements strictly hold true regarding the system $Ax = b$?

(A) The system always has at least one solution for any $b \\in \\mathbb{R}^m$.

(B) If a solution exists, it cannot be unique.

(C) The column space of $A$ cannot span $\\mathbb{R}^m$.

(D) The null space of $A$ must contain non-zero vectors.

7\. \*\*(NAT)\*\* Let $S = \\{v\_1, v\_2, v\_3, v\_4\\}$ be a set of vectors in $\\mathbb{R}^4$. The matrix $A = \[v\_1, v\_2, v\_3, v\_4]$ has rank $2$. The matrix $B = \[v\_1, v\_2, v\_3]$ has rank $2$. The matrix $C = \[v\_1, v\_2]$ has rank $1$. What is the minimum number of vectors you must remove from $S$ to form a linearly independent set that spans the exact same subspace as $S$?



\*\*Calculus \& Optimization: Deep Execution (Day 1 Strict Scope)\*\*



8\. \*\*(NAT)\*\* Evaluate the exact numerical value of the limit using Maclaurin and Leibniz principles:



$$\\lim\_{x \\to 0} \\frac{\\int\_0^{x^2} (\\sin(t) - t) dt}{x^8}$$





9\. \*\*(MSQ)\*\* Consider the piecewise function defined on $\[-2, 2]$:

$f(x) = \\begin{cases} x^2 \\sin(1/x) \& \\text{if } x \\neq 0 \\\\ 0 \& \\text{if } x = 0 \\end{cases}$

Which of the following theorems apply to $f(x)$ on the interval $\[-2, 2]$?

(A) Extreme Value Theorem (it must attain an absolute maximum and minimum).

(B) Rolle's Theorem (there exists a point $c$ where $f'(c) = 0$).

(C) Mean Value Theorem (differentiability strictly holds on the open interval $(-2, 2)$).

(D) The derivative $f'(x)$ is bounded on $\[-2, 2]$.

10\. \*\*(NAT)\*\* Find the exact absolute minimum value of the function $f(x) = \\vert{}x^2 - 4\\vert{} + \\vert{}x - 1\\vert{}$ on the closed interval $\[0, 3]$.

11\. \*\*(NAT)\*\* A polynomial $P(x)$ of degree $3$ satisfies $P(0) = 1$, $P(1) = 2$, and $P(2) = 1$. According to the Mean Value Theorem (and its extension, Rolle's Theorem), what is the minimum number of distinct real roots the equation $P''(x) = 0$ must have in the interval $(0, 2)$?

12\. \*\*(MSQ)\*\* Let $f(x)$ and $g(x)$ be differentiable functions on $\\mathbb{R}$ such that $f(0) = g(0)$ and $f'(x) > g'(x)$ for all $x > 0$. Which of the following must definitively be true?

(A) $f(x) > g(x)$ for all $x > 0$.

(B) $f(x) < g(x)$ for all $x < 0$.

(C) $\\lim\_{x \\to \\infty} (f(x) - g(x)) = \\infty$.

(D) The function $h(x) = f(x) - g(x)$ is strictly increasing for $x > 0$.

13\. \*\*(NAT)\*\* Determine the exact maximum possible area of a rectangle that can be inscribed between the x-axis and the curve $y = 12 - x^2$, with its base resting on the x-axis.

14\. \*\*(NAT)\*\* Evaluate the following limit to two decimal places. \*(Hint: Use algebraic factorization, do not loop L'Hôpital).\*



$$\\lim\_{x \\to 1} \\frac{x^{10} - 1}{x^4 - 1}$$







\*\*Probability \& Statistics: Deep Execution (Day 1 Strict Scope)\*\*



15\. \*\*(NAT)\*\* A factory has $100$ identical-looking boxes. $99$ of the boxes contain $1$ red ball and $1$ blue ball. The remaining $1$ box contains $2$ red balls. You select a box uniformly at random and draw one ball from it blindly. It is red. What is the exact probability (fraction) that the \*second\* ball remaining in that specific box is also red?

16\. \*\*(MSQ)\*\* Let $A, B, C$ be three events where $P(A) = 0.4$, $P(B) = 0.5$, and $P(C) = 0.6$. If it is known that $A$ and $B$ are mutually exclusive, which of the following statements are mathematically impossible?

(A) $A$, $B$, and $C$ are pairwise independent.

(B) $P(A \\cap B \\cap C) = 0.1$.

(C) $P(A \\cup B \\cup C) = 1.0$.

(D) $P(A \\mid C) = P(B \\mid C) = 0$.

17\. \*\*(NAT)\*\* Ten people hand their hats to a cloakroom attendant. The attendant mixes them up and hands exactly one hat back to each person randomly. Let $X$ be the number of people who receive their own hat back, AND the person standing immediately to their right also receives their own hat back (assume they stand in a straight line, so there are $9$ such adjacent pairs). Using indicator variables, find the exact expected value $E\[X]$.

18\. \*\*(NAT)\*\* An automated testing suite generates a sequence of independent test cases. Each test case has a probability $p = 0.2$ of triggering a specific memory leak. The suite stops generating cases the moment the memory leak is triggered. What is the exact expected number of test cases generated? \*(Hint: Use the formula for the expectation of a geometric sequence using infinite series limits, or the memoryless property).\*

19\. \*\*(MSQ)\*\* Let $P(A) = x$ and $P(B) = y$. If $A \\subset B$ (A is a strict subset of B), which of the following properties are absolutely true?

(A) $x \\le y$

(B) $P(A \\cup B) = y$

(C) $P(A \\mid B) = \\frac{x}{y}$

(D) $P(B \\mid A) = 1$

20\. \*\*(NAT)\*\* An urn contains $a$ white balls and $b$ black balls. A ball is drawn at random and its color is noted. The ball is then returned to the urn, along with $c$ additional balls of the \*same color\*. A second ball is then drawn. Prove algebraically that the probability the second ball is white is exactly equal to the probability the first ball was white. Enter the final simplified probability fraction in terms of $a$ and $b$ (assume $c$ cancels out). Provide the exact numerator and denominator ratio.



\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*



\### \*\*Deep Dive: The Intuition of Rank \& Nullity\*\*



Stop thinking about Rank and Nullity as rows and columns. Think of a matrix as an \*\*Information Filter\*\* (a function that processes data), and vectors as the data passing through it.



\* \*\*The Vector Space (The Input):\*\* If a matrix has $n$ columns, it accepts data with $n$ dimensions. (This is the total information).

\* \*\*Rank (The Survivors):\*\* The Rank is the exact number of dimensions of information that \*survive\* the matrix transformation and make it out the other side.

\* \*\*Null Space / Nullity (The Graveyard):\*\* The Null Space is the set of all data vectors that the matrix completely destroys (crushes to zero: $Ax = 0$). The Nullity is the number of dimensions lost.



\*\*Rank-Nullity Theorem translated:\*\*

$\\text{Total Information In} = \\text{Information Survived} + \\text{Information Destroyed}$

$\\text{Columns} = \\text{Rank} + \\text{Nullity}$



\*\*Why does $\\text{Rank}(AB) \\le \\text{Rank}(B)$?\*\*

Imagine a two-step data pipeline. Data $x$ goes through filter $B$ first, then filter $A$. So, $ABx = A(Bx)$.



\* If filter $B$ compresses 5D data down to 3D data ($\\text{Rank}(B) = 3$), the absolute maximum amount of information entering $A$ is 3 dimensions.

\* Filter $A$ cannot magically invent new data out of thin air. It can only let those 3 dimensions pass through, or destroy even more.

\* Therefore, the final output $\\text{Rank}(AB)$ can never be larger than what $B$ initially let through.



\*\*Why does $\\text{Nullity}(AB) \\ge \\text{Nullity}(B)$?\*\*



\* If filter $B$ destroys a vector $x$ (meaning $Bx = 0$), that dead vector is passed to $A$.

\* $A(0)$ will always equal $0$. Once $B$ destroys data, $A$ cannot bring it back to life.

\* Therefore, every single vector that $B$ destroyed is \*also\* destroyed by the total system $AB$. Furthermore, $A$ might destroy \*additional\* vectors that $B$ let live.

\* Thus, the total data destroyed by the system ($\\text{Nullity}(AB)$) must be greater than or equal to the data destroyed by $B$ alone.



\---



\### \*\*Day 1: Deep Execution - Batch 2 (Questions 21-32)\*\*



\*Scope Strictness Check: Only Subspaces, Ranks, Systems, Limits, Global/Local Extrema, MVT/Rolle's, Bayes, Total Probability, Indicators, and Bounds.\*



\#### \*\*Linear Algebra\*\*



21\. \*\*(NAT)\*\* Consider a non-homogeneous system of equations $Ax = b$ where $A$ is a $4 \\times 3$ matrix. The augmented matrix $\[A\\vert{}b]$ has a rank of $3$. Which of the following must be the exact value of $\\text{Rank}(A)$ for the system to have a \*unique\* solution?

22\. \*\*(MSQ)\*\* Let $A$ be a $3 \\times 5$ real matrix and $B$ be a $5 \\times 3$ real matrix. Given that the matrix product $AB = I\_3$ (the $3 \\times 3$ identity matrix), which of the following statements are absolute mathematical certainties?

(A) $\\text{Rank}(A) = 3$ and $\\text{Rank}(B) = 3$.

(B) The $5 \\times 5$ matrix $BA$ is non-singular.

(C) $\\text{Nullity}(BA) = 2$.

(D) The system $Bx = 0$ has only the trivial solution $x=0$.

23\. \*\*(NAT)\*\* The system of equations is given by:

$x + 2y + 3z = 1$

$2x + 5y + 5z = 3$

$3x + 7y + 8z = k^2 - 1$

For what exact value of $k^2$ is the system inconsistent (i.e., has zero solutions)?

24\. \*\*(MSQ)\*\* Let $W$ be the set of all $2 \\times 2$ matrices $M$ such that $M \\begin{pmatrix} 1 \\\\ 2 \\end{pmatrix} = \\begin{pmatrix} 0 \\\\ 0 \\end{pmatrix}$. Which of the following are true?

(A) $W$ is not a valid subspace of the $2 \\times 2$ matrix space.

(B) $W$ is a subspace with a dimension of $2$.

(C) $W$ is a subspace with a dimension of $3$.

(D) Every matrix in $W$ is a singular matrix.



\#### \*\*Calculus \& Optimization\*\*



25\. \*\*(NAT)\*\* Evaluate the exact numerical value of the limit using L'Hôpital/Leibniz rules:



$$\\lim\_{x \\to 0} \\frac{\\int\_0^x t^2 e^{t^2} dt}{x^3}$$







Provide the answer as a simplified fraction.

26\. \*\*(NAT)\*\* Find the sum of the absolute maximum and absolute minimum values of the function $f(x) = 2x^3 - 9x^2 + 12x$ evaluated strictly on the closed interval $\[0, 3]$.

27\. \*\*(MSQ)\*\* Let $f(x)$ be a function that is continuous on $\[a, b]$ and differentiable on $(a, b)$. If $f(a) = f(b)$, Rolle's Theorem guarantees a $c \\in (a, b)$ where $f'(c) = 0$. Which of the following functions violate the \*conditions\* of Rolle's Theorem on the interval $\[-1, 1]$?

(A) $f(x) = \\vert{}x^2 - 1\\vert{}$

(B) $f(x) = 1 / x^2$

(C) $f(x) = x^{1/3}$

(D) $f(x) = \\cos(x)$

28\. \*\*(NAT)\*\* A polynomial $f(x) = x^4 + ax^3 + bx^2 + cx + d$ has a local minimum at $x = 0$ with value $2$, and a local maximum at $x = 1$ with value $3$. Find the exact value of the y-intercept of the derivative graph $y = f'(x)$.



\#### \*\*Probability \& Statistics\*\*



29\. \*\*(NAT)\*\* Three factories X, Y, and Z produce 50%, 30%, and 20% of a company's microchips, respectively. The probability that a chip is defective is 1% for X, 2% for Y, and 3% for Z. A chip is selected at random and found to be defective. What is the exact probability (fraction) that it was produced by Factory Z?

30\. \*\*(NAT)\*\* Ten married couples (20 people total) are assigned seats entirely at random in a single row of 20 chairs at a theater. Using indicator variables, what is the exact expected number of couples that end up sitting strictly next to each other?

31\. \*\*(MSQ)\*\* Let events $A$ and $B$ have probabilities $P(A) = 0.7$ and $P(B) = 0.6$. Which of the following bounds are mathematically enforced?

(A) $P(A \\cap B) \\ge 0.3$

(B) $P(A \\cap B) \\le 0.6$

(C) $P(A \\cup B) \\ge 0.7$

(D) $P(A \\mid B) \\le 1.0$

32\. \*\*(NAT)\*\* An urn contains 3 red balls and 2 black balls. You draw two balls sequentially \*without replacement\*. Let Event A be "The first ball is red" and Event B be "The second ball is black." Calculate the exact conditional probability $P(A \\mid B)$.



\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*



\*\*Verdict: 9/12. An exceptionally sharp execution.\*\*



\### \*\*The Corrections\*\*



\*\*1. (Calculus Q25) The Leibniz Limit Slip\*\*



\* \*\*Your Answer:\*\* `0.5`

\* \*\*The Correction:\*\* You perfectly applied Leibniz to differentiate the integral, yielding $x^2 e^{x^2}$ in the numerator. However, you slipped on the denominator's derivative. The derivative of $x^3$ is \*\*$3x^2$\*\*, not $2x^2$.

\* $\\lim\_{x \\to 0} \\frac{x^2 e^{x^2}}{3x^2} = \\lim\_{x \\to 0} \\frac{e^{x^2}}{3} = \\mathbf{\\frac{1}{3}}$ (or $0.333$).



\*\*2. (Calculus Q27) The "Violate" Trap\*\*



\* \*\*Your Answer:\*\* `A, D`

\* \*\*The Correction:\*\* You found the functions that \*satisfy\* Rolle's Theorem, but the question specifically asked which functions \*\*violate\*\* its conditions.

\* (A) $f(x) = \\vert{}x^2 - 1\\vert{}$ inside $(-1, 1)$ simplifies exactly to the polynomial $1 - x^2$, which is perfectly differentiable. (Satisfies).

\* (B) $f(x) = 1/x^2$ is discontinuous at $x=0$. (Violates).

\* (C) $f(x) = x^{1/3}$ has a vertical tangent at $x=0$, so $f'(0)$ is undefined. (Violates).

\* (D) $\\cos(x)$ is infinitely differentiable. (Satisfies).





\* \*\*Correct Answer:\*\* \*\*B, C\*\*.



\*\*3. (Probability Q30) Couples Expected Value\*\*



\* \*\*Your Answer:\*\* `0.5`

\* \*\*The Correction:\*\* Let's use the Indicator bypass to destroy the combinatorics.

\* There are 20 chairs, meaning there are exactly \*\*$19$ adjacent pairs of chairs\*\*.

\* Let $I\_j = 1$ if the $j$-th adjacent pair is occupied by a married couple.

\* Who sits in the first chair of the pair doesn't matter. Once they sit down, there are 19 people left standing. Exactly $1$ of those 19 is their spouse. Thus, the probability the spouse takes the adjacent chair is $\\frac{1}{19}$.

\* $E\[I\_j] = \\frac{1}{19}$.

\* Total Expected Couples = $\\sum\_{j=1}^{19} E\[I\_j] = 19 \\times \\frac{1}{19} = \\mathbf{1}$.







\---



\### \*\*Day 1: Final Deep Execution - Batch 3 (Questions 33-44)\*\*



This is the final batch of Day 1. We are testing the absolute limits of the Day 1 syllabus scope. Take a breath, watch your denominators, and read the MSQ constraints carefully.



\#### \*\*Linear Algebra\*\*



33\. \*\*(NAT)\*\* Let $A$ be a $3 \\times 4$ real matrix and $B$ be a $4 \\times 5$ real matrix. Both $A$ and $B$ have a rank of exactly 3. Let $C = AB$. Find the exact dimension of the null space (nullity) of the matrix $C^T$ (the transpose of $C$).

34\. \*\*(MSQ)\*\* Let $A$ be an $n \\times n$ idempotent matrix (meaning $A^2 = A$). Which of the following statements are mathematically guaranteed?

(A) The determinant of $A$ can only be $0$ or $1$.

(B) $\\text{Rank}(A) + \\text{Nullity}(A) = n$.

(C) The trace of $A$ is strictly equal to the rank of $A$.

(D) The matrix $I - A$ is also idempotent.

35\. \*\*(NAT)\*\* Consider a subspace $W$ of $\\mathbb{R}^4$ defined by the span of the vectors $v\_1 = (1, 2, 0, -1)^T$, $v\_2 = (2, 4, 0, -2)^T$, and $v\_3 = (0, 0, 1, 1)^T$. What is the exact dimension of this subspace?

36\. \*\*(NAT)\*\* The system of equations $Ax = 0$ has $5$ variables. The matrix $A$ has $3$ rows. If the system has exactly $2$ linearly independent solutions, what is the exact rank of matrix $A$?



\#### \*\*Calculus \& Optimization\*\*



37\. \*\*(NAT)\*\* Evaluate the exact numerical value of the limit using Maclaurin series expansions:



$$\\lim\_{x \\to 0} \\frac{\\ln(1+x^2) - x^2}{x^4}$$







Provide the answer as a simplified fraction.

38\. \*\*(MSQ)\*\* Consider the function $f(x) = \\begin{cases} x^2 \& \\text{if } x \\text{ is rational} \\\\ 0 \& \\text{if } x \\text{ is irrational} \\end{cases}$. Which of the following statements are true?

(A) $f(x)$ is everywhere discontinuous.

(B) $f(x)$ is continuous at exactly one point: $x = 0$.

(C) $f(x)$ is differentiable at exactly one point: $x = 0$.

(D) $f'(0)$ does not exist.

39\. \*\*(NAT)\*\* An open-top cylindrical can is to be manufactured to hold exactly $1000\\pi$ cubic centimeters of liquid. To minimize the cost of metal used, the surface area must be minimized. Find the exact optimal radius of the base of the cylinder (in cm).

40\. \*\*(NAT)\*\* The function $f(x) = \\vert{}x-1\\vert{} + \\vert{}x-2\\vert{} + \\vert{}x-3\\vert{}$ attains its absolute global minimum at some point $x = c$. Find the exact value of $c$. \*(Hint: Think about the geometry of the derivative or the sum of absolute distances).\*



\#### \*\*Probability \& Statistics\*\*



41\. \*\*(NAT)\*\* Let $X$ be a continuous random variable with the probability density function $f(x) = 2x$ for $0 \\le x \\le 1$, and $0$ otherwise. Find the exact variance of $X$. Provide the answer as a simplified fraction $p/q$, and output the sum $p+q$.

42\. \*\*(MSQ)\*\* Let $A, B$, and $C$ be three mutually independent events in a sample space, each with a probability of $0.5$. Which of the following statements are true?

(A) $P(A \\cap B \\cap C) = 0.125$

(B) $P(A \\cup B) = 0.75$

(C) Events $(A \\cap B)$ and $C$ are mathematically independent.

(D) $P(A \\mid B \\cup C) = 0.5$

43\. \*\*(NAT)\*\* A monkey types exactly 5 random letters uniformly at random from the 26-letter English alphabet (allowing repetitions). Using indicator variables, what is the exact expected number of times the sequence "AI" appears in the 5-letter output? (Provide as a simplified fraction).

44\. \*\*(NAT)\*\* An urn contains $3$ green balls and $4$ yellow balls. Three balls are drawn at random \*without replacement\*. If exactly $2$ of the drawn balls are known to be yellow, what is the exact probability that the \*very first\* ball drawn was green?