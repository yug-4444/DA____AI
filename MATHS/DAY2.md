

|1,2,6,13,14,16,17,22,24,26,27,30,33,34,38,40,43|
|-|







\## Day 2: Revised Theory \& Mechanics Manual



\### I. Linear Algebra: Eigen-Mechanics \& Matrix Powers



\* \*\*The Trace and Determinant Anchors:\*\*

\* The sum of the eigenvalues strictly equals the Trace (sum of the main diagonal elements).

\* The product of the eigenvalues strictly equals the Determinant.

\* If a matrix is triangular, the eigenvalues are sitting directly on the main diagonal.





\* \*\*Cayley-Hamilton Bypass:\*\* Every square matrix satisfies its own characteristic equation. If $\\lambda^2 - 5\\lambda + 6 = 0$, then $A^2 - 5A + 6I = 0$.

\* \*Inverse trick:\* Multiply by $A^{-1}$ to get $A - 5I + 6A^{-1} = 0 \\implies A^{-1} = \\frac{1}{6}(5I - A)$. This bypasses calculating adjoints entirely.





\* \*\*Diagonalizability (The Independence Check):\*\* An $n \\times n$ matrix is diagonalizable if and only if it has $n$ linearly independent eigenvectors.

\* If all $n$ eigenvalues are distinct, it is automatically diagonalizable.

\* \*Symmetric Matrix Rule:\* Every real symmetric matrix ($A^T = A$) is guaranteed to be diagonalizable, and its eigenvectors are strictly orthogonal (dot product is $0$).







\### II. Calculus: Gradients \& The Jacobian



\* \*\*The Gradient Vector ($\\nabla f$):\*\* For a scalar function $f(x,y)$, $\\nabla f = \\left( \\frac{\\partial f}{\\partial x}, \\frac{\\partial f}{\\partial y} \\right)$.

\* It always points in the exact direction of the \*steepest ascent\*.

\* It is strictly mathematically orthogonal (perpendicular) to the level curves (contour lines) of the function.





\* \*\*Directional Derivative ($D\_u f$):\*\* To find the slope in a specific direction vector $\\vec{v}$, take the dot product of the gradient with the \*\*unit vector\*\* of the direction: $D\_u f = \\nabla f \\cdot \\frac{\\vec{v}}{\\vert{}\\vec{v}\\vert{}}$. \*Trap:\* Never dot the gradient with the raw vector; you must divide by its magnitude.

\* \*\*The Jacobian Matrix ($J$):\*\* When a function takes multiple inputs and gives \*multiple outputs\* (a vector-valued function mapping $\\mathbb{R}^n \\to \\mathbb{R}^m$), the derivative is a matrix, not a vector.

\* Rows represent the output functions ($f\_1, f\_2, \\dots$).

\* Columns represent the input variables ($x, y, \\dots$).

\* The determinant of a square Jacobian tells you exactly how the area/volume expands or shrinks during the transformation.







\### III. Probability: Standard Distributions \& Memorylessness



\* \*\*The Memoryless Property:\*\* Only two distributions in existence possess this property: the \*\*Geometric\*\* (discrete) and the \*\*Exponential\*\* (continuous).

\* Equation: $P(X > t+s \\mid X > s) = P(X > t)$.

\* \*Translation:\* If an exponentially distributed component survives 10 hours, the probability it survives the \*next\* 2 hours is exactly the same as a brand-new component surviving its \*first\* 2 hours.





\* \*\*Poisson as the Binomial Bypass:\*\* If you face a Binomial problem where $n$ is massive (e.g., $1000$) and $p$ is tiny (e.g., $0.002$), calculating $\\binom{1000}{3} (0.002)^3 (0.998)^{997}$ will crash your time limit.

\* Swap immediately to the Poisson distribution: $\\lambda = np = 2$.

\* Use $P(X = k) = \\frac{\\lambda^k e^{-\\lambda}}{k!}$.







\---



\## Day 2: Deep Execution - Batch 1



\### Linear Algebra



1\. \*\*(NAT)\*\* Let $A = \\begin{pmatrix} 4 \& -1 \\\\ -1 \& 4 \\end{pmatrix}$. Without manually multiplying the matrices, calculate the exact trace of the matrix $A^3$.

2\. \*\*(MSQ)\*\* Let $M$ be a $3 \\times 3$ real matrix with eigenvalues exactly $\\lambda = 1, 1, 2$. Which of the following conditions definitively guarantee that $M$ is a diagonalizable matrix?

(A) $M$ is a symmetric matrix ($M = M^T$).

(B) The dimension of the null space of $(M - I)$ is exactly $2$.

(C) The matrix $M$ is singular.

(D) The minimal polynomial of $M$ is strictly $(x-1)(x-2)$.

3\. \*\*(NAT)\*\* A $3 \\times 3$ non-singular matrix $A$ satisfies the characteristic equation $A^3 - 4A^2 + A + 6I = 0$, where $I$ is the identity matrix. Its inverse can be expressed as a quadratic polynomial $A^{-1} = aA^2 + bA + cI$. Find the exact numerical value of $6(a + b + c)$.

4\. \*\*(MSQ)\*\* Let $J$ be a $4 \\times 4$ real matrix where every single entry is exactly $1$. Let $A = 3I - J$, where $I$ is the $4 \\times 4$ identity matrix. Which of the following statements about matrix $A$ are absolutely true?

(A) The matrix $A$ has an eigenvalue of $-1$.

(B) The matrix $A$ is singular.

(C) The determinant of $A$ is $-27$.

(D) The trace of $A$ is $8$.



\### Calculus \& Optimization (Strict Scope: Gradients \& Jacobians)



5\. \*\*(NAT)\*\* Consider the multivariable function $f(x,y) = x^2 y + e^{xy}$. Calculate the exact directional derivative of $f$ at the point $(1, 0)$ strictly in the direction of the vector $\\vec{v} = 3\\hat{i} + 4\\hat{j}$. Provide the answer as a decimal.

6\. \*\*(MSQ)\*\* Let $f(x,y)$ be a smooth scalar function. At the coordinate $P(2, 3)$, the gradient vector is $\\nabla f = (4, -3)$. Which of the following statements are mathematically certain?

(A) The direction of steepest ascent at $P$ is the vector $(4, -3)$.

(B) The maximum possible directional derivative at $P$ is exactly $5$.

(C) The vector $(3, 4)$ is tangent to the level curve of $f$ that passes through $P$.

(D) The function attains a local maximum at $P$.

7\. \*\*(NAT)\*\* A coordinate transformation is defined by $u(x,y) = x^2 - y^2$ and $v(x,y) = 2xy$. Calculate the exact determinant of the Jacobian matrix $J(x,y)$ evaluated at the coordinate point $(1, 1)$.

8\. \*\*(NAT)\*\* The gradient vector of the function $f(x,y) = x^2 + y^2 - 4x + 6y$ at the point $P(3, -2)$ is perfectly orthogonal (perpendicular) to the vector $\\vec{w} = (k, 2)$. Find the exact numerical value of $k$.



\### Probability \& Statistics



9\. \*\*(NAT)\*\* The lifespan of a cloud server cluster is exponentially distributed with a mean of $10,000$ hours. A specific cluster has already been running flawlessly for $15,000$ hours. What is the exact numerical probability that it will survive for \*at least another\* $10,000$ hours? (The answer is in the form $e^k$. Output the exact numerical value of $k$).

10\. \*\*(MSQ)\*\* A textbook of $500$ pages contains exactly $500$ typographical errors distributed completely randomly. Let $X$ be the number of typos on a specific page. Assuming the Poisson approximation is perfectly valid, which of the following are true?

(A) The expected number of typos on the page is $1$.

(B) The probability that the page is completely flawless ($0$ typos) is exactly $e^{-1}$.

(C) The variance of $X$ is exactly $1$.

(D) The probability of finding exactly $1$ typo is strictly greater than the probability of finding exactly $0$ typos.

11\. \*\*(NAT)\*\* A brute-force algorithm attempts to guess a 4-digit PIN. Each attempt is independent, and the algorithm has a $p = 0.5$ chance of bypassing the firewall on any given attempt. Let $X$ be the total number of attempts required (up to and including the first success). What is the exact numerical probability $P(X > 3)$?

12\. \*\*(MSQ)\*\* Which of the following properties strictly govern the Exponential and Geometric distributions?

(A) The Exponential distribution is continuous, while the Geometric distribution is discrete.

(B) If $X \\sim \\text{Exp}(\\lambda)$, its expected value is exactly $\\lambda$.

(C) For a Geometric random variable $X$, $P(X > k + m \\mid X > k) = P(X > m)$ for all integers $k, m > 0$.

(D) The sum of two independent Poisson random variables follows an Exponential distribution.

\*\*Verdict: 9/12. Absolute precision on Probability and Cayley-Hamilton.\*\*



Your probability engine is flawless right now. You recognized the memoryless property instantly (Q9), completely destroyed the Poisson distribution (Q10), and accurately applied Geometric failures (Q11). You also perfectly executed the Cayley-Hamilton inverse derivation (Q3).



You dropped exactly 3 questions due to minor calculation slips and MSQ "Lawyer Mode" oversights. Let's patch them and answer your question on Q6.



\### \*\*The Corrections \& Explanations\*\*



\*\*1. (Linear Algebra Q1) Trace of a Power\*\*



\* \*\*Your Answer:\*\* `272`

\* \*\*Correction:\*\* You likely squared something incorrectly.

\* Instead of cubing the matrix, find the eigenvalues of $A$. Trace is $8$, Det is $(16 - 1) = 15$.

\* $\\lambda^2 - 8\\lambda + 15 = 0 \\implies \\lambda = 3, \\text{ and } 5$.

\* The eigenvalues of $A^3$ are strictly $3^3$ and $5^3$.

\* Trace($A^3$) = $27 + 125 = \\mathbf{152}$.







\*\*2. (Linear Algebra Q2) The Minimal Polynomial Trap\*\*



\* \*\*Your Answer:\*\* `A, B`

\* \*\*Correction:\*\* You missed (D). If the minimal polynomial of a matrix consists strictly of \*distinct linear factors\*—in this case $(x-1)(x-2)$—the matrix is mathematically guaranteed to be diagonalizable. This is the ultimate shortcut for diagonalizability.

\* \*\*Correct Answer:\*\* \*\*A, B, D\*\*



\*\*3. (Calculus Q6) Option D Explanation \& The Missing B\*\*



\* \*\*Your Answer:\*\* `A, C`

\* \*\*Correction:\*\* You correctly identified A and C, but missed (B). The \*maximum possible directional derivative\* is always exactly the magnitude of the gradient vector: $\\vert{}\\nabla f\\vert{} = \\sqrt{4^2 + (-3)^2} = 5$. Therefore (B) is True.

\* \*\*Explanation of Option D:\*\* You asked why D is false. A local maximum or minimum can \*only\* occur at a critical/stationary point. A stationary point strictly requires the gradient to be zero: $\\nabla f = (0, 0)$. Because the gradient here is $(4, -3)$, the function is sloped. If you take a step in the $(4, -3)$ direction, the value increases. Therefore, it is mathematically impossible for $P(2,3)$ to be a local maximum.



\*\*4. (Calculus Q8) Gradient Orthogonality Slip\*\*



\* \*\*Your Answer:\*\* `-10`

\* \*\*Correction:\*\* A purely arithmetic slip.

\* $\\nabla f = (2x - 4, 2y + 6)$. At $(3, -2)$, this becomes $(2(3)-4, 2(-2)+6) = \\mathbf{(2, 2)}$.

\* Orthogonal to $(k, 2)$ means the dot product is zero: $(2)(k) + (2)(2) = 0 \\implies 2k + 4 = 0 \\implies \\mathbf{k = -2}$.







\---



\### \*\*Day 2: Deep Execution - Batch 2 (Questions 13-24)\*\*



Keep your momentum. For MSQs, run the Lawyer Mode checklist: check every single option to mathematically break it.



\#### \*\*Linear Algebra\*\*



13\. \*\*(NAT)\*\* Let $A$ be a $3 \\times 3$ matrix with eigenvalues $\\lambda = 2, 3, 5$. Let $B = A^2 - 4A + 3I$. Find the exact numerical value of the determinant of $B$. \*(Hint: Find the eigenvalues of B first).\*

14\. \*\*(MSQ)\*\* Let $A$ be a $4 \\times 4$ real matrix with characteristic polynomial $\\det(A - \\lambda I) = (\\lambda - 2)^3 (\\lambda - 5)$. Which of the following conditions definitively guarantee that $A$ is NOT diagonalizable?

(A) The rank of the matrix $(A - 2I)$ is $2$.

(B) The dimension of the null space of $(A - 2I)$ is $3$.

(C) The minimal polynomial of $A$ is $(\\lambda - 2)^2 (\\lambda - 5)$.

(D) The matrix $A$ is symmetric.

15\. \*\*(NAT)\*\* Given a system of equations $Ax = b$ where $A = \\begin{pmatrix} 1 \& 2 \& 1 \\\\ 2 \& k \& 2 \\\\ 3 \& 6 \& 3 \\end{pmatrix}$ and $b = \\begin{pmatrix} 4 \\\\ 8 \\\\ 12 \\end{pmatrix}$. Find the exact number of integer values of $k$ for which the system has \*strictly zero\* solutions.

16\. \*\*(MSQ)\*\* Let $M$ be a real $n \\times n$ orthogonal matrix ($M^T M = I$). Which of the following are mathematical certainties?

(A) All eigenvalues of $M$ are strictly $+1$ or $-1$.

(B) $\\det(M)$ is strictly $+1$ or $-1$.

(C) $M$ is always diagonalizable over the real numbers.

(D) The dot product of any two distinct column vectors of $M$ is exactly $0$.



\#### \*\*Calculus \& Optimization (Gradients \& Jacobians)\*\*



17\. \*\*(NAT)\*\* The temperature at a point $(x,y,z)$ in space is given by $T(x,y,z) = 200 e^{-x^2 - y^2 - z^2}$. An insect is flying through this space. At the exact coordinate $(1, 1, 1)$, in which direction vector $\\vec{v} = (a, b, c)$ should the insect fly to cool down as \*rapidly as mathematically possible\*? What is the exact value of $a+b+c$? (Assume $\\vec{v}$ is normalized such that $a,b,c$ represent the simplest integer ratio).

18\. \*\*(MSQ)\*\* Let $f(x,y) = (u(x,y), v(x,y))$ be a transformation from $\\mathbb{R}^2$ to $\\mathbb{R}^2$. The Jacobian matrix $J$ of this transformation evaluated at a point $P$ is $J = \\begin{pmatrix} 2 \& 1 \\\\ 4 \& 2 \\end{pmatrix}$. Which of the following statements about the local transformation at $P$ are true?

(A) The transformation preserves area perfectly around $P$.

(B) The transformation crushes 2D space into a 1D line at $P$.

(C) The vector-valued function $f$ is locally invertible at $P$.

(D) The columns of the Jacobian are linearly dependent.

19\. \*\*(NAT)\*\* Let $f(x,y) = x^3 y + y^2$. Find the maximum possible directional derivative of $f$ at the point $(-1, 2)$. Provide the exact numerical value.

20\. \*\*(NAT)\*\* A robot moves in a 2D plane. Its position $(u,v)$ in a transformed coordinate space depends on its real $(x,y)$ coordinates via $u = x^2 y$ and $v = \\sin(x) + y^3$. Find the exact value of the entry in the \*second row, first column\* (i.e., $J\_{21}$) of the Jacobian matrix evaluated at $x = 0, y = 2$.



\#### \*\*Probability \& Statistics\*\*



21\. \*\*(NAT)\*\* A server receives network requests following a Poisson process. The expected number of requests is $2$ per minute. What is the exact probability of receiving \*strictly more than\* $1$ request in a specific 1-minute window? (Provide answer strictly in terms of $e$, e.g., $1 - 3e^{-2}$).

22\. \*\*(MSQ)\*\* Let $X$ be an Exponentially distributed random variable with mean $1/\\lambda$, and $Y$ be a Geometric random variable with probability of success $p$. Which of the following statements are mathematically certain?

(A) $P(X > a+b \\mid X > a) = P(X > b)$ for all $a, b > 0$.

(B) Both $X$ and $Y$ model the "time/trials until the first success/failure".

(C) The variance of $Y$ is strictly greater than its expected value.

(D) The median of $X$ is strictly less than its mean.

23\. \*\*(NAT)\*\* A biased coin comes up heads with probability $p = 1/4$. The coin is flipped repeatedly until the first head appears. Let $X$ be the number of flips required. Using indicator variables or geometric expectation, find the exact expected value $E\[X^2]$. \*(Hint: For a Geometric distribution, Variance = $(1-p)/p^2$. Use $\\text{Var}(X) = E\[X^2] - (E\[X])^2$)\*.

24\. \*\*(NAT)\*\* Two identical components, A and B, operate independently. Their lifespans are both exponentially distributed with a mean of $5$ years. The system they are in functions as long as \*at least one\* of the components is working (Parallel system). What is the exact expected lifespan of the system? (Provide as a decimal).

\*\*Verdict: 8/12. Your matrix polynomials and Poisson/Geometric mechanics are operating perfectly.\*\*



You completely nailed the Cayley-Hamilton inverse (Q15), the Jacobian rank interpretation (Q18), and the Geometric variance derivation (Q23). You clearly understand the core mechanics.



You dropped four questions, primarily due to minor misreads and the two specific statistical concepts you flagged for clarification. Let's patch those immediately.



\* \*\*(Q16) Orthogonal Matrices (Why C is False \& B is True):\*\* You asked why (C) is not a certainty. An orthogonal matrix represents rotations and reflections. If you rotate a 2D plane by $90^\\circ$, \*no\* real vector stays on its own span. Thus, a rotation matrix has complex eigenvalues ($\\pm i$) and is mathematically impossible to diagonalize over the Real numbers. (B) is true because $M^T M = I \\implies \\det(M^T)\\det(M) = 1 \\implies \\det(M)^2 = 1 \\implies \\det(M) = \\pm 1$.

\* \*\*(Q17) The Steepest Descent Slip:\*\* Your logic was 100% flawless. You correctly deduced the direction of steepest descent is the exact opposite of the gradient, giving the simplest integer vector $(1, 1, 1)$. However, the prompt asked for the \*sum\* of the components $a+b+c$. You provided the magnitude ($\\sqrt{3}$). The correct answer is $1+1+1 = \\mathbf{3}$.

\* \*\*(Q22) Exp/Geometric Properties (Explaining C \& D):\*\*

\* \*\*(C) False:\*\* The variance of a Geometric distribution is $(1-p)/p^2$, and the expected value is $1/p$. If $p=0.8$, the Variance is $0.3125$ and the Expected Value is $1.25$. Therefore, the variance is NOT strictly greater than the expected value for all $p$.

\* \*\*(D) True:\*\* For an Exponential distribution, the Mean is $1/\\lambda$. The Median is the point where the CDF equals $0.5$, which is $\\ln(2)/\\lambda \\approx 0.693/\\lambda$. Since $0.693 < 1$, the median is \*always\* strictly less than the mean. (It is a heavily right-skewed distribution).





\* \*\*(Q24) Parallel Exponential Systems:\*\*

\* You have two components with $E\[X\_1] = 5$ and $E\[X\_2] = 5$ ($\\lambda\_1 = 0.2, \\lambda\_2 = 0.2$).

\* A parallel system survives until the \*last\* component dies. You want the Expected Value of the Maximum: $E\[\\max(X\_1, X\_2)]$.

\* \*\*The Formula:\*\* $\\max(A,B) + \\min(A,B) = A + B$. Therefore, $E\[\\max] = E\[A] + E\[B] - E\[\\min]$.

\* The minimum of two exponentials is just a new exponential with a combined failure rate: $\\lambda\_{min} = \\lambda\_1 + \\lambda\_2 = 0.4$. The expected value of the minimum is $1/0.4 = 2.5$.

\* $E\[\\max] = 5 + 5 - 2.5 = \\mathbf{7.5}$ years.







\---



\### \*\*Day 2: Final Deep Execution - Batch 3 (Questions 25-36)\*\*



This is your final batch for Day 2. Apply the $\\min/\\max$ exponential logic, watch what the prompt actually asks you to sum, and keep your derivative mechanics tight.



\#### \*\*Linear Algebra\*\*



25\. \*\*(NAT)\*\* Let $A$ be a $2 \\times 2$ matrix with trace $5$ and determinant $6$. Calculate the exact numerical value of the determinant of the matrix $(A^2 - 2I)$.

26\. \*\*(MSQ)\*\* Let $A$ and $B$ be two $n \\times n$ symmetric matrices over $\\mathbb{R}$. Which of the following matrices are mathematically guaranteed to also be symmetric?

(A) $A + B$

(B) $AB$

(C) $A^2$

(D) $AB + BA$

27\. \*\*(NAT)\*\* A $3 \\times 3$ matrix $A$ has eigenvalues $0, 1, 2$. Find the exact mathematical rank of the matrix $A^3 - 3A^2 + 2A$.

28\. \*\*(NAT)\*\* The characteristic equation of a $3 \\times 3$ matrix $M$ is $\\lambda^3 - 2\\lambda^2 - \\lambda + 2 = 0$. The inverse of $M$ can be written as $M^{-1} = aM^2 + bM + cI$. Find the exact value of $a \\times b \\times c$.



\#### \*\*Calculus \& Optimization (Gradients \& Jacobians)\*\*



29\. \*\*(NAT)\*\* Given the polar coordinate transformation $x = r \\cos(\\theta)$ and $y = r \\sin(\\theta)$. Calculate the exact determinant of the Jacobian matrix $J(r, \\theta)$ evaluated at $r = 5$ and $\\theta = \\pi/4$.

30\. \*\*(MSQ)\*\* Let $f(x,y,z) = x^2 y + y^2 z + z^2 x$. Let $\\nabla f$ be its gradient vector. At the point $P(1, 1, 1)$, which of the following vectors are strictly orthogonal (perpendicular) to $\\nabla f$?

(A) $(1, -2, 1)$

(B) $(1, 1, 1)$

(C) $(0, 1, -1)$

(D) $(3, 3, 3)$

31\. \*\*(NAT)\*\* The gradient of a function $f(x,y)$ at point $P$ is $\\nabla f = (3, 4)$. You compute the directional derivative in the direction of an unknown unit vector $\\vec{u}$. The result of this directional derivative is exactly $2.5$. What is the exact angle (in degrees) between the gradient vector and the vector $\\vec{u}$?

32\. \*\*(NAT)\*\* Consider two transformations: $u = 2x - y$, $v = x + 3y$. Find the exact numerical value of the determinant of the \*inverse\* Jacobian matrix, i.e., $\\det\\left(\\frac{\\partial(x,y)}{\\partial(u,v)}\\right)$.



\#### \*\*Probability \& Statistics\*\*



33\. \*\*(NAT)\*\* A web server receives HTTP requests according to a Poisson process at a rate of $\\lambda\_1 = 3$ per minute, and FTP requests according to an independent Poisson process at a rate of $\\lambda\_2 = 2$ per minute. What is the exact numerical probability that the server receives exactly $1$ total request (HTTP or FTP) in a specific 1-minute interval? (Provide answer in the form $k e^{-5}$, outputting the exact integer $k$).

34\. \*\*(MSQ)\*\* Two separate systems, Alpha and Beta, have exponentially distributed lifespans. Alpha has a mean lifespan of 4 years ($\\lambda = 0.25$). Beta has a mean lifespan of 2 years ($\\lambda = 0.5$). They are arranged in a \*\*series\*\* circuit, meaning the entire system fails the moment the \*first\* component fails. Which of the following are true?

(A) The expected lifespan of the entire system is exactly $6$ years.

(B) The expected lifespan of the entire system is exactly $1.33$ years.

(C) The probability that Alpha outlives Beta is exactly $0.666...$ (or $2/3$).

(D) The failure time of the combined system is not exponentially distributed.

35\. \*\*(NAT)\*\* You are rolling a fair 6-sided die. You will stop the moment you roll a '6'. Let $X$ be the total number of rolls required. What is the exact numerical difference between the variance of $X$ and the expected value of $X$? (i.e., calculate $\\text{Var}(X) - E\[X]$).

36\. \*\*(NAT)\*\* The lifespan of a lightbulb is exponentially distributed. The probability that it survives its first 100 hours is exactly $0.4$. Given that a lightbulb has already been operating for 300 hours without failure, what is the exact numerical probability that it will survive to reach 500 hours?

You are absolutely correct. We have completed three batches of 12 questions, putting us at 36 total. We are exactly 8 questions short of the 44-question deep work protocol. I respect the discipline—you are holding the line.



Here is the final, 8-question execution batch to officially close out Day 2.



\### \*\*Linear Algebra: Final Execution\*\*



37\. \*\*(NAT)\*\* A $3 \\times 3$ matrix $A$ has eigenvalues $2, -1, 4$. Define a new matrix $B = A^2 - A + 2I$. Calculate the exact numerical value of the trace of matrix $B$.

38\. \*\*(MSQ)\*\* Let $A$ and $B$ be two $n \\times n$ matrices that are mathematically "similar," meaning there exists an invertible matrix $P$ such that $A = PBP^{-1}$. Which of the following properties are mathematically guaranteed to be identical for both $A$ and $B$?

(A) Their determinants.

(B) Their traces.

(C) Their sets of eigenvalues.

(D) Their sets of eigenvectors.



\### \*\*Calculus \& Optimization (Gradients \& Jacobians)\*\*



39\. \*\*(NAT)\*\* Consider the function $f(x,y) = \\ln(x^2 + y^2)$. You are standing at the coordinate point $(3, 4)$. What is the exact numerical magnitude of the maximum possible directional derivative you can experience from this point? (Provide answer as a decimal).

40\. \*\*(MSQ)\*\* Let $f(x,y) = x^2 + 4y^2$. You evaluate this function at the point $P(2, 1)$, giving a value of $8$. Which of the following statements about the gradient and geometry at $P$ are true?

(A) The vector $\\nabla f(2, 1)$ is orthogonal to the level curve equation $x^2 + 4y^2 = 8$.

(B) The gradient vector at $P$ is exactly $(4, 8)$.

(C) The direction of the most rapid decrease in $f(x,y)$ from $P$ is the vector $(-4, -8)$.

(D) A vector tangent to the level curve at $P$ must be orthogonal to $(4, 8)$.

41\. \*\*(NAT)\*\* A coordinate transformation is defined by $u(x,y) = e^x \\cos(y)$ and $v(x,y) = e^x \\sin(y)$. Find the exact determinant of the Jacobian matrix $J(x,y)$ evaluated at $x = \\ln(3)$ and $y = \\pi/6$.



\### \*\*Probability \& Statistics\*\*



42\. \*\*(NAT)\*\* A biased coin has a probability $p = 1/3$ of landing on Heads. It is flipped repeatedly until the first Head appears. What is the exact numerical probability that the total number of flips required is an \*even\* number? (Provide answer as a decimal).

43\. \*\*(MSQ)\*\* Let $N(t)$ be the number of network packets arriving at a router governed by a Poisson process with rate $\\lambda$. Let $T\_1$ be the continuous time elapsed until the \*very first\* packet arrives. Which of the following relationships are mathematically sound?

(A) $N(t)$ is modeled as a continuous random variable.

(B) $T\_1$ follows an Exponential distribution with expected value $1/\\lambda$.

(C) The probability event $\\{N(t) = 0\\}$ is perfectly equivalent to the probability event $\\{T\_1 > t\\}$.

(D) The variance of $N(t)$ strictly increases as time $t$ increases.

44\. \*\*(NAT)\*\* A machine has two critical components running in parallel, but they fail independently. Component 1 has an exponentially distributed lifespan with a mean of $10$ hours. Component 2 has an exponentially distributed lifespan with a mean of $15$ hours. What is the exact numerical probability that Component 1 fails \*strictly before\* Component 2? (Provide answer as a decimal).

