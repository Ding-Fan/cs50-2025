#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Maximum number of candidates
#define MAX 9

// preferences[i][j] is the number of voters who prefer candidate i over candidate j.
int preferences[MAX][MAX];

// locked[i][j] means candidate i is locked in over candidate j.
bool locked[MAX][MAX];

// Pair structure: each pair has a winner and a loser.
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates (using cs50's string type)
string candidates[MAX];

// Array to hold all pairs. The maximum possible pairs is MAX * (MAX - 1) / 2.
pair pairs[MAX * (MAX - 1) / 2];

// Global variables to keep track of the number of pairs and candidates.
int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool set_ranks(int ranks[]);
bool check_cycle(int start, int current);
int string_includes(string array[], int array_length, string target);
int set_candidates(int argc, string argv[]);

int main(int argc, string argv[])
{
    int result = 0;
    
    result = set_candidates(argc, argv);

    if(result != 0)
    {
        return result;
    }

    // Initialize the locked graph to false (no edges locked in initially)
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // Create an array to record one voter's ranks.
        int ranks[candidate_count];

        // Use the vote-based set_ranks to fill the ranks array.
        if (!set_ranks(ranks))
        {
            // If an invalid vote is encountered, exit.
            return 3;
        }

        printf("Ranks: ");
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", ranks[j]);
        }
        printf("\n");

        // Update preferences given this voter's ranks.
        record_preferences(ranks);

        printf("Preferences:\n");
        for (int i = 0; i < candidate_count; i++)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                printf("%i ", preferences[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();

    return 0;
}

int set_candidates(int argc, string argv[])
{
    // Ensure at least one candidate is provided
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Set candidate_count and check if within maximum limit
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    // Populate the array of candidates from command-line arguments
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    return 0;
}

int string_includes(string array[], int array_length, string target)
{
    for (int i = 0; i < array_length; i++)
    {
        if (strcmp(array[i], target) == 0)
        {
            return i;
        }
    }
    return -1;
}

bool vote(int rank, string name, int ranks[])
{
    int candidate_index = string_includes(candidates, candidate_count, name);
    if (candidate_index == -1)
    {
        printf("Invalid vote.\n");
        return false;
    }
    ranks[rank] = candidate_index;
    return true;
}

bool set_ranks(int ranks[])
{
    for (int rank = 0; rank < candidate_count; rank++)
    {
        string name = get_string("Rank %i: ", rank + 1);
        if (!vote(rank, name, ranks))
        {
            return false;
        }
    }
    return true;
}

void record_preferences(int ranks[])
{
    // For example, if ranks is [2, 0, 1], then candidate 2 > candidate 0 > candidate 1.
    // which means
    // candidate 2 > candidate 0
    // candidate 2 > candidate 1
    // candidate 0 > candidate 1

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

void add_pairs(void)
{
    // for example, we have a, b, c
    // we will check
    // a vs b, which is check a > b or b > a
    // a vs c, which is check a > c or c > a
    // b vs c, which is check b > c or c > b

    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            // Do nothing on ties.
        }
    }
}

void sort_pairs(void)
{
    // calculate the strength of each pair
    // compare the strength use bubble sort 
    bool swapped;
    do
    {
        swapped = false;
        for (int i = 0; i < pair_count - 1; i++)
        {
            int strength_i =
                preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
            int strength_j =
                preferences[pairs[i + 1].winner][pairs[i + 1].loser] - preferences[pairs[i + 1].loser][pairs[i + 1].winner];

            if (strength_i < strength_j)
            {
                pair temp = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = temp;
                swapped = true;
            }
        }
    } while (swapped);
}

bool check_cycle(int start, int current)
{
    // if a == a, it is a cycle
    if (current == start)
    {
        return true;
    }

    // for each candidate
    // if locked[a][b] is true, which means a > b
    // call check_cycle(start, b)
    // the start is always the same
    // the current will change if
    // for each candidate, there is a candidate > current
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[current][i])
        {
            if (check_cycle(start, i))
            {
                return true;
            }
        }
    }
    return false;
}

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Tentatively add the pair.
        locked[pairs[i].winner][pairs[i].loser] = true;
        // If this creates a cycle, undo and do not lock the pair.
        if (check_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
}

/*
 * print_winner:
 * Determines and prints the winner of the election.
 * The winner is the candidate with no incoming locked edges.
 */
void print_winner(void)
{
    for (int candidate = 0; candidate < candidate_count; candidate++)
    {
        bool is_winner = true;
        for (int other = 0; other < candidate_count; other++)
        {
            if (locked[other][candidate])
            {
                is_winner = false;
                break;
            }
        }
        if (is_winner)
        {
            printf(candidates[candidate]);
            printf("\n");
            return;
        }
    }
    // Fallback in case no winner is found (this should not happen)
    printf("No winner found.\n");
}
