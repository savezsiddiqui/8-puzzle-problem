#include <bits/stdc++.h>
using namespace std;

int ex = 1;

void print(int (*start)[3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << start[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int manhattanDistance(int (*start)[3], int (*goal)[3])
{
    int dist = 0;
    int corr_i, corr_j;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (start[i][j] != 0)
            {
                corr_i = (start[i][j] - 1) / 3;
                corr_j = (start[i][j] - 1) % 3;
                dist += abs(corr_i - i) + abs(corr_j - j);
            }
        }
    }
    return dist;
}

void up(int start[][3])
{
    int i, j, f1 = 0, x, y;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (start[i][j] == 0)
            {
                x = i;
                y = j;
                f1 = 1;
                break;
            }
        }
        if (f1 == 1)
            break;
    }
    if (x != 0)
        swap(&start[x][y], &start[x - 1][y]);
}

void down(int (*start)[3])
{
    int i, j, f2 = 0, x, y;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (start[i][j] == 0)
            {
                x = i;
                y = j;
                f2 = 1;
                break;
            }
        }
        if (f2 == 1)
            break;
    }
    if (x != 2)
        swap(&start[x][y], &start[x + 1][y]);
}

void left(int (*start)[3])
{
    int i, j, f3 = 0, x, y;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (start[i][j] == 0)
            {
                x = i;
                y = j;
                f3 = 1;
                break;
            }
        }
        if (f3 == 1)
            break;
    }
    if (y != 0)
        swap(&start[x][y], &start[x][y - 1]);
}

void right(int (*start)[3])
{
    int i, j, f4 = 0, x, y;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (start[i][j] == 0)
            {
                x = i;
                y = j;
                f4 = 1;
                break;
            }
        }
        if (f4 == 1)
            break;
    }
    if (y != 2)
        swap(&start[x][y], &start[x][y + 1]);
}

void copy1(int (*start)[3], int (*start1)[3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            start[i][j] = start1[i][j];
        }
    }
}

void hillclimb(int (*start)[3], int (*goal)[3], int (*start1)[3])
{
    int h_val;
    int h_val_next[4] = {0, 0, 0, 0};
    bool nxt = true;
    while (nxt == true)
    {
        int f = 0;
        print(start);
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (start[i][j] != goal[i][j])
                {
                    f = 1;
                    break;
                }
            }
        }
        if (f == 0)
        {
            cout << endl
                 << " Solution reached " << endl
                 << " Number of explored states : " << ex << endl;
            return;
        }
        h_val = manhattanDistance(start, goal);
        up(start);
        h_val_next[0] = manhattanDistance(start, goal);
        copy1(start, start1);
        down(start);
        h_val_next[1] = manhattanDistance(start, goal);
        copy1(start, start1);
        right(start);
        h_val_next[2] = manhattanDistance(start, goal);
        copy1(start, start1);
        left(start);
        h_val_next[3] = manhattanDistance(start, goal);
        copy1(start, start1);

        int index, m = INT_MAX, c = -1;
        for (int i = 0; i < 3; i++)
        {
            if (h_val_next[i] < h_val && h_val_next[i] < m)
            {
                m = h_val_next[i];
                index = i;
                c++;
            }
        }
        if (c != -1)
        {
            ex++;
            if (index == 0)
            {
                up(start);
                up(start1);
                h_val = h_val_next[0];
            }
            else if (index == 1)
            {
                down(start);
                down(start1);
                h_val = h_val_next[1];
            }
            else if (index == 2)
            {
                right(start);
                right(start1);
                h_val = h_val_next[2];
            }
            else if (index == 3)
            {
                left(start);
                left(start1);
                h_val = h_val_next[3];
            }
        }
        else
            nxt = false;
    }
}

int main()
{
    int st1[3][3] = {{1, 2, 0}, {4, 5, 3}, {7, 8, 6}};
    int st[3][3] = {{1, 2, 0}, {4, 5, 3}, {7, 8, 6}};
    int goal1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    hillclimb(st, goal1, st1);
    return 0;
}
