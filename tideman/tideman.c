#include <cs50.h>
#include <stdio.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
int pair_count;
pair result[MAX * (MAX - 1) / 2];
int candidate_count;
int winners[MAX];
int losers[MAX];
int locked_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void sort_winners(int start);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    // place them in candidates array
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
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
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{

    // TODO
    // i is for each voter
    // j is rank 0, 1, 2
    // match name to a number
    // shove number into ranks
    for (int k = 0; k < candidate_count; k++)
    {
        if (strcasecmp(name, candidates[k]) == 0)
        {
            ranks[rank] = k;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int z = 0; z < candidate_count; z++)
    // TODO
    // update global variable int preferences[MAX][MAX];
    {
        for (int n = z + 1; n < candidate_count; n++)
        {
            preferences[ranks[z]][ranks[n]]++;
            printf("%s over %s: %i\n", candidates[ranks[z]], candidates[ranks[n]], preferences[ranks[z]][ranks[n]]);
        }
    }
    return;
}

void sort_winners(int i)
{
    if (i >= candidate_count)
    {
        return;
    }
        for (int j = i + 1; j < candidate_count; j++)
        {
            // for each pair of candidates (j is the next candidate to i), we check to see who is the winner
            if (preferences[i][j] > preferences[j][i])
            {
                // we then add the winner and the loser to the pair array called pairs.
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                printf("paircount: %i , i %s, j %s\n", pair_count, candidates[i], candidates[j]);
                //printf("loser: %s, %i\n", candidates[j], pairs[pair_count].loser);
                // pair count was set to 0 and now we increment it with every pair added.
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].loser = i;
                pairs[pair_count].winner = j;
                printf("pair count: %i , j %s, i %s\n", pair_count, candidates[j], candidates[i]);
                //printf("loser: %s, %i\n", candidates[i], pairs[pair_count].loser);
                pair_count++;
            }
        }
    sort_winners(i + 1);
}


// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    // list all preferences
    sort_winners(0);
    printf("%i\n", pair_count);
    return;

}

void conquer(pair array[], pair left[], pair right[], int midpoint, int size)
{
    // sort the array and populate the array result[]

    int right_number = 0; // ith pair on the left
    int left_number = 0; // ith pair on the right

    int i = 0;
    while (left_number < midpoint && right_number < (size - midpoint))
    {
        int right_strength = preferences[right[right_number].winner][right[right_number].loser] - preferences[right[right_number].loser][right[right_number].winner];
        int left_strength = preferences[left[left_number].winner][left[left_number].loser] - preferences[left[left_number].loser][left[left_number].winner];

        if (right_strength > left_strength)
        {
            result[i] = right[right_number];
            right_number++;
            i++;
        }
        else
        {
            result[i] = left[left_number];
            left_number++;
            i++;
            //printf("left number: %i\n", left_number);
            printf("result[%i], winner: %i, loser: %i\n", i, result[i].winner, result[i].loser);
        }
    }
    while (left_number < midpoint)
    {
        result[i++] = left[left_number++];
    }
    while (right_number < (size - midpoint))
    {
        result[i++] = right[right_number++];
    }
    for (int z = 0; z < size; z++)
    {
        array[z] = result[z];
    }
      // comparing the first character of left with the right
}

void divide(pair array[], int size)
{
    // we first set the midpoint to size (initially paircount) divided by 2
    int midpoint = size / 2;

    //printf("midpoint: %i, size: %i\n", midpoint, size);
    if (size <= 1)
    {
        return;
    }
    // if size is still divisible by 2, execute the following:
    else
    {
        // create a left array with max no. of pair being the midpoint
        pair left[midpoint];
        pair right[size - midpoint];
        for (int i = 0; i < midpoint; i++)
        {
            left[i] = array[i];
        }
        for (int j = midpoint; j < size; j++)
        {
            right[j - midpoint] = array[j];
        }
        divide(left, midpoint);
        divide(right, size - midpoint);
        conquer (array, left, right, midpoint, size);
    }
}
// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    divide(pairs, pair_count);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //bool locked[MAX][MAX];
    // using BFS to solve this problem
    // for each in results, if it does not have any cycles then lock the pair

    // function to check if there is a cycle
    // start would be the loser of the pair
    // initialise a queue
    // put start in queue
    // mark start as visited
    // while q is not empty
    
}

// Print the winner of the election
void print_winner(void)
{
    return;
}