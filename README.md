# HotRace

An in-memory key-value lookup tool that reads a dictionary and a list of queries from stdin and answers them through a compressed trie (radix tree) with sorted, binary-searched children. Written as a team for the HotRace rush at 42 Berlin, where the goal is the fastest correct program.

**Stack:** C · Make    **Context:** 42 Berlin curriculum | HotRace rush (48-hour team exercise), 2024

## Overview

HotRace is a 42 "rush": a short team project with a fixed input/output contract, graded on correctness and speed. The program receives key/value pairs, then keys to look up, and must print each value or a "Not found" message.

The implementation stores keys in a **compressed trie**:

- **Path compression:** a chain of single-child nodes is collapsed into one edge labelled with a substring, so tree depth depends on the number of branching points rather than key length
- **Prefix sharing:** keys with a common prefix share the nodes for that prefix
- **Sorted children:** each node keeps its children in an array sorted by the first character of their edge label, and `search_match()` finds the right child with a binary search
- **No substring copies:** an edge label is a `[start, end)` slice into the original key string, so splitting an edge only adjusts indices

## Build & run

```bash
make        # ./hotrace
make clean  # remove object files
make fclean # remove object files and the binary
make re     # rebuild from scratch
```

Compiled with `cc -Wall -Wextra -Werror -g`.

```bash
./hotrace < input.txt
```

## Input format

1. **Dictionary:** alternating lines of key and value, ended by an empty line
2. **Queries:** one key per line until end of input

For each query the program prints the stored value, or `<key>: Not found.` A key that appears twice in the dictionary keeps its first value, and `Key already existing` is printed to stderr.

### Example

```bash
$> printf 'Hello\nWorld\napple\nred\n\nHello\nAnimal\napple\n' | ./hotrace
World
Animal: Not found.
red
```

More inputs with shared prefixes:

```bash
printf 'application\napp1\napplicant\napp2\napple\nfruit\n\napplication\napple\ntest\n' | ./hotrace
```

## How it works

### Data structures

```c
typedef struct s_entry
{
    char    *key;      // full key string this edge label points into
    char    *value;    // NULL for internal nodes created by a split
    int     start;     // edge label = key[start..end)
    int     end;
} t_entry;

typedef struct s_trie
{
    t_entry         entry;
    struct s_trie   **next;      // children, sorted by first label character
    int             child_num;
} t_trie;
```

### Insertion (`ft_trie_insert`)

Starting at the root, the insert walks down: binary-search the child whose label starts with the next key character, then consume the longest common prefix of the label and the remaining key (`common_prefix_len()`). When no child matches, one of four cases applies (`choose_operation()`):

| Remaining key | Label fully matched | Action |
|---------------|---------------------|--------|
| not empty | yes | `add_node_curr`: insert a new leaf child at its sorted position |
| empty | yes | `add_value_curr`: attach the value to the existing node |
| empty | no | `split_edge`: split the label, the new middle node holds the value |
| not empty | no | `split_and_add_node`: split the label into a node with two children, the old subtree and the new leaf, in sorted order |

### Lookup (`ft_trie_search`)

The same walk as insertion; the key is found if it is fully consumed exactly at the end of a node's label and that node has a value. Lookup cost is O(k · log c) for a key of length k and at most c children per node.

### Memory

Child arrays are reallocated one slot larger on each insert, and `ft_clean_trie()` frees the whole tree recursively at exit.

## Notes

- Input is read with a modified `get_next_line(fd, &len)` that also returns the line length. Its `BUFFER_SIZE` defaults to 1 in `includes/get_next_line.h`.
- Values are stored with their trailing newline and written back unchanged.

## Project structure

```
hotrace/
├── Makefile
├── includes/
│   ├── hotrace.h              # t_entry, t_trie, prototypes
│   └── get_next_line.h
└── srcs/
    ├── hotrace.c              # main: init, read dictionary, answer queries, free
    ├── utils.c                # node creation, common prefix, binary search, cleanup
    ├── utils2.c               # input parsing, insert case selection
    ├── create_art.c           # insert, edge splitting, search
    └── get_next_line/
        ├── get_next_line.c
        └── get_next_line_utils.c
```

## Team & credits

Built as a team at the 42 Berlin HotRace rush by Nam Lap Vu ([42navalkrinzhaslattt](https://github.com/42navalkrinzhaslattt), 42 login `nam-vu`) and `dkoca` (42 login). Both appear in the source file headers; the repository history is a single upload commit, so individual contributions are not tracked here.
