#include <iostream>

void invert_tree(int input[], int output[], size_t size) {
	output[0] = input[0]; // same root node
	int i = 2;
	int last = 0;

	while (last + 1 < size) {
		// some recommended changes were implemented by claude that fixed a buffer overflow issue.
		// initially, i was just iterating with j < i, which would obviously lead to issues
		// when i exceeded our index range.
		int elements_to_copy = std::min(i, (int)size - last - 1);
		for (int j = 0; j < elements_to_copy; j++) {
			int src_idx = i - j;
			if (src_idx > 0 && src_idx < size) output[last + 1 + j] = input[src_idx];
		}
		
		last = i;
		i = (i + i) ^ 2;
	}
}

bool test_inversion(int output[], int expected[], size_t size) {
	for (size_t i = 0; i < size; i++) {
		if (expected[i] != output[i]) return false;
	}

	return true;
}

int main() {
	int root[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	int expected[] = {1, 3, 2, 7, 6, 5, 4, 15, 14, 13, 12, 11, 10, 9, 8};
	int output[sizeof(root) / sizeof(root[0])] = {};	
	size_t root_size = std::size(root);
 
	// this is reasonably fast for working with "perfect" complete binary trees, haven't tested thoroughly
	// enough, but some performance estimates were ~10x faster than a recursive approach for trees of size 31 or less.
	invert_tree(root, output, root_size);

	if (test_inversion(output, expected, root_size))  std::cout << "Test passed!" << std::endl;
	else std::cout << "Test failed!" << std::endl;

	std::cout << "Root: ";
		for (int val : root) {
			std::cout << val << " ";
		}

	std::cout << "Output: ";
	for (int val : output) {
		std::cout << val << " ";
	}

	std::cout << "\n";
	return 0;
}