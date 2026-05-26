import numpy as np

class LinearSystem:
    def __init__(self, A, b):
        self.a = np.array(A, dtype=float)
        self.b = np.array(b, dtype=float)
        self.n = self.b.size
        
    def solve_and_verify(self):
        # FIXED: Indented the entire method body
        aug = np.hstack([self.a, self.b.reshape(-1, 1)])

        # Forward elimination
        for i in range(self.n):
            pivot_i = np.argmax(abs(aug[i:, i])) + i
            
            # Swap current row with pivot row
            aug[[i, pivot_i]] = aug[[pivot_i, i]]
            
            if np.isclose(aug[i, i], 0):
                continue  # Skip if pivot is zero
                
            # Normalize the pivot row
            aug[i, :] = aug[i, :] / aug[i, i]
            
            # Eliminate below
            for j in range(i + 1, self.n):
                factor = aug[j, i]
                aug[j, :] -= factor * aug[i, :]

        # --- Check reduced rows ---
        infinite_solutions = False
        for row in aug:
            # Check if all coefficients in the row are practically zero
            if np.allclose(row[:-1], 0):
                # If coefficients are 0 but the result is not 0, it's inconsistent
                if not np.isclose(row[-1], 0):
                    raise ValueError("Inconsistent system: No solution exists.")
                else:
                    # If both coefficients and result are 0, we have a free variable
                    infinite_solutions = True
                    
        if infinite_solutions:
            raise ValueError("Infinite solutions: System underdetermined.")

        # Back substitution
        x = np.zeros(self.n)
        for i in range(self.n - 1, -1, -1):
            x[i] = aug[i, -1] - np.dot(aug[i, i+1:self.n], x[i+1:])

        # Verification
        residual = np.dot(self.a, x) - self.b
        print(f"Verification (Ax - b): {residual}")
        if np.allclose(residual, 0):
            print("Status: SUCCESS. Manual Gaussian Elimination verified.")
        print("Solution vector x:", x)


# --- Execution ---
if __name__ == "__main__":
    A_input = [[1, 2, -1,1], [2, 1, 1,-1], [1, -1, 2,2],[-1,2,1,-3]]
    b_input = [2, 5, 3,-4]

    system = LinearSystem(A_input, b_input)
    
    # Added a try-except block to gracefully handle the ValueErrors
    try:
        system.solve_and_verify()
    except ValueError as e:
        print(f"System Check Failed: {e}")