#include <iostream>

void invert_tree(int input[], int output[], size_t size) {
	output[0] = input[0]; // same root node
	int level_size = 2;
	int prev_level_idx = 1;

	while (prev_level_idx < size) {
		// some recommended changes were implemented by claude that fixed a buffer overflow issue.
		// initially, i was just iterating with i < last_level_idx, which would obviously lead to issues
		// when last_level_idx exceeded our index range.
		int elements_to_copy = std::min(level_size, (int)size - prev_level_idx);
		for (int i = 0; i < elements_to_copy; i++) {
			int src_idx = prev_level_idx + elements_to_copy - 1 - i;
			if (src_idx > 0 && src_idx < size) output[prev_level_idx + i] = input[src_idx];
		}
		
		prev_level_idx += level_size;
		level_size *= 2;
	}
}

bool test_inversion(int output[], int expected[], size_t size) {
	for (size_t i = 0; i < size; i++) {
		if (expected[i] != output[i]) return false;
	}

	return true;
}

int main() {
	int root[] = {1,2,3,4,5,6,7,8,9,10};
	int expected[] = {1,3,2,7,6,5,4,10,9,8};
	// int root[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	// int expected[] = {1, 3, 2, 7, 6, 5, 4, 15, 14, 13, 12, 11, 10, 9, 8};
	size_t root_size = std::size(root);
	int output[root_size] = {};	
 
	invert_tree(root, output, root_size);

	if (test_inversion(output, expected, root_size))  std::cout << "Test passed!" << std::endl;
	else std::cout << "Test failed!" << std::endl;

	std::cout << "Root: ";
	for (int val : root) {
		std::cout << val << " ";
	}

	std::cout << "\nOutput: ";
	for (int val : output) {
		std::cout << val << " ";
	}

	std::cout << "\n";
	return 0;
}