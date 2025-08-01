# HotRace - High-Performance Key-Value Store

A lightning-fast algorithmic project implementing a key-value storage and retrieval system using a **Compressed Trie (Radix Tree)** data structure. HotRace is designed for competitive programming environments where speed and efficiency are paramount.

## 🏁 About HotRace

HotRace is a competitive programming challenge focused on creating the fastest possible key-value store implementation. This project uses a sophisticated **Compressed Trie** (also known as a Radix Tree) to achieve optimal performance for both storage and retrieval operations.

## ⚡ Why Trie?

Our implementation uses a **Compressed Trie** for several performance advantages:

- **O(k) Search Time**: Where k is the length of the key, independent of the number of stored entries
- **Memory Efficient**: Path compression reduces memory usage by combining single-child nodes
- **Prefix Sharing**: Common prefixes are stored only once, optimizing memory usage
- **Binary Search**: Child nodes are sorted and accessed using binary search for O(log n) child lookup
- **Cache Friendly**: Sequential memory access patterns improve cache performance

## 🚀 Features

- **High-Performance Storage**: Optimized trie structure with path compression
- **Fast Retrieval**: Logarithmic search within node children
- **Memory Efficient**: Compressed paths reduce memory overhead
- **Error Handling**: Graceful handling of missing keys with "Not found" messages
- **Clean Memory Management**: Proper cleanup and deallocation

## 📋 Usage

### Compilation

```bash
make
```

### Running the Program

```bash
./hotrace
```

### Input Format

The program operates in two phases:

1. **Dictionary Phase**: Store key-value pairs
   - Enter a key and press Enter
   - Enter the corresponding value and press Enter
   - Press Enter on an empty line to end dictionary input

2. **Query Phase**: Search for stored values
   - Enter keys to search for their values
   - Keys not found will display "Key: Not found."

### Example

```bash
$> ./hotrace
Hello
World
Hello
Goodbye

Hello
World
Animal
Animal: Not found.
Hello
Goodbye

$>
```

## 🏗️ Implementation Details

### Data Structures

#### Trie Node (`t_trie`)
```c
typedef struct s_trie
{
    t_entry         entry;      // Key-value entry with start/end indices
    struct s_trie   **next;     // Array of child nodes
    int             child_num;  // Number of child nodes
} t_trie;
```

#### Entry (`t_entry`)
```c
typedef struct s_entry
{
    char    *key;      // The key string
    char    *value;    // The associated value
    int     start;     // Start index in the key
    int     end;       // End index in the key
} t_entry;
```

### Key Algorithms

#### Path Compression
- **Edge Compression**: Multiple characters stored in single nodes
- **Common Prefix Detection**: Efficient prefix matching using `common_prefix_len()`
- **Dynamic Splitting**: Nodes split when new branches are needed

#### Binary Search Optimization
- Child nodes maintained in sorted order by first character
- `search_match()` function provides O(log n) child lookup
- Recursive binary search implementation

#### Memory Management
- Dynamic allocation for child arrays
- Proper cleanup with `ft_clean_trie()`
- Memory-efficient node creation

## 📁 Project Structure

```
hotrace/
├── Makefile                    # Build configuration
├── includes/
│   ├── hotrace.h              # Main header file
│   └── get_next_line.h        # Input handling header
├── srcs/
│   ├── hotrace.c              # Main program entry point
│   ├── utils.c                # Core trie operations
│   ├── utils2.c               # Input parsing and initialization
│   ├── create_art.c           # Trie insertion and search algorithms
│   └── get_next_line/         # Input reading utilities
│       ├── get_next_line.c
│       └── get_next_line_utils.c
└── README.md                  # This file
```

## 🔧 Build System

### Available Commands

```bash
make        # Build the project
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Rebuild from scratch
```

### Compiler Flags

- `-Wall -Werror -Wextra`: Strict error and warning checking
- `-g`: Debug information for development
- `-g3`: Extended debug information

## 🎯 Performance Characteristics

### Time Complexity
- **Insertion**: O(k) where k is the key length
- **Search**: O(k) where k is the key length
- **Child Lookup**: O(log c) where c is the number of children

### Space Complexity
- **Best Case**: O(n) where n is total characters in all unique prefixes
- **Worst Case**: O(n × k) where n is number of keys and k is average key length

## 🏆 Competitive Advantages

1. **Path Compression**: Reduces tree depth and memory usage
2. **Binary Search**: Optimizes child node lookup
3. **Memory Locality**: Sequential access patterns improve cache performance
4. **Minimal Overhead**: Efficient data structures with minimal metadata
5. **Fast Prefix Matching**: Optimized common prefix detection

## 🧪 Testing

Test your implementation with various datasets:

```bash
# Small dataset
echo -e "apple\nred\nbanana\nyellow\n\napple\nbanana\ncherry" | ./hotrace

# Large dataset with common prefixes
echo -e "application\napp1\napplicant\napp2\napple\nfruit\n\napplication\napple\ntest" | ./hotrace
```

## 🚧 Development Notes

- The implementation uses a custom `get_next_line()` function for efficient input reading
- Error handling includes proper memory cleanup and user-friendly error messages
- The trie structure supports dynamic resizing of child arrays
- Path compression is handled through the `split_edge()` and `split_and_add_node()` functions

## 📄 License

This project is part of the 42 School curriculum and follows the school's academic guidelines.

## 👥 Contributors

- **nam-vu**: Core implementation and algorithm design
- **dkoca**: Code optimization and testing

---

*Built for speed. Optimized for victory. 🏁*
