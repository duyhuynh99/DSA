#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>

using namespace std;

int** init_board()
{
    int** t = new int*[5];
    for(int i = 0; i < 5; i++)
    {
        t[i] = new int[5];
        if(i == 0)
        {
            for(int j = 0; j < 5; j++)
                t[i][j] = 1;
        }
        if(i == 4)
        {
            for(int j = 0; j < 5; j++)
                t[i][j] = -1;
        }
    }
    t[1][0] = 1; t[1][4] = 1; t[2][0] = 1;
    t[2][4] = -1; t[3][0] = -1; t[3][4] = -1;
    return t;
}

int** copy_board(int** board)
{
    int** n_b = new int*[5];
    for(int i = 0; i < 5; i++)
    {
        n_b[i] = new int[5];
        for(int j = 0; j < 5; j++)
        {
            n_b[i][j] = board[i][j];
        }
    }
    return n_b;
}

void print_board(int** board)
{
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(board[4-i][j] == 1)
                cout << "X ";
            else if(board[4-i][j] == -1)
                cout << "O ";
            else
                cout << "- ";
        }
        cout << endl;
    }
}

struct Position
{
    int x; int y;
    Position(){x = y = 0;}
    Position(int a, int b)
    {
        x = a; y = b;
    }
};

struct Move
{
    Position pos_start, pos_end;
    Move(Position s, Position e)
    {
        pos_start = s; pos_end = e;
    }
};

void copy_board(int** temp, int** board);

vector<Position> ganh(int** board, Move m, int player);

vector<Position> adj(int** board, int** marked, Position pos, int player);

bool check(int** board, Position pos);

bool chet(int** board, int** marked, Position pos);

int** init_marked();

void destroy_marked(int** marked);

vector<Position> vay(int** board, Move m, int player);

vector<Position> Around(Position pos);

Move move_have_gone(int **current_board, int **previous_board, int player);

vector<Move> bay_or_mo(int **current_board, int **previous_board, int player);

void act_move(int** board, Move m, int player);

void act_move(int** board, int** previous_board, Move m, int player);

vector<Move> get_valid_moves(int **current_board, int **previous_board, int player);

int get_score(int **board, Move m, int player);

int get_max_point_after(int** board, Move m, int player);

Move select_move(int **current_board, int **previous_board, int player);

void play(int first);

int main()
{
    play(1);
    /*//--------------------------------------------------------------- 
    // Case 1
    int sub_board[5][5] = {0,  0, 0, 0, 0, 
                           0,  0, 0, 0, 0,
                           1,  0, 0, 0, 0,
                           0,  1, 1, 0, 0,
                          -1, -1, 1, 0, 0};

    int** board = new int*[5];
    for(int i = 0; i < 5; i++)
    { 
        board[i] = new int[5];
        for (int j = 0; j < 5; j++) board[i][j] = sub_board[i][j];
    }

    Position start(2,0), end(3,0);
    Move m(start,end);

    print_board(board);

    vector<Position> vay_move = vay(board, m, 1);
    cout<<vay_move.size()<<"\n";
    act_move(board, m, 1);

    // --------------------------------------------------------------- 
    // Case 2

    int sub_board2[5][5] = { 0,  0 ,  0, 0, 0, 
                             0,  0 ,  0, 0, 0,
                             1,  1 ,  0, 0, 0,
                            -1,  1 ,  1, 1, 0,
                            -1,  0 , -1, 1, 0};
    for(int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) board[i][j] = sub_board2[i][j];
    
    print_board(board);

    Position start2(3,2), end2(4,1);
    Move m2(start2,end2);

    vector<Position> vay_move2 = vay(board, m2, 1);
    cout<<vay_move2.size()<<"\n";
    act_move(board, m2, 1);

    // --------------------------------------------------------------- 
    // Case 3

    int sub_board3[5][5] = { 0,  0 ,  0, 0,  0, 
                             1,  1 ,  1, 1,  1,
                            -1, -1 , -1, 0, -1,
                             1,  1 ,  1, 1,  0,
                             0,  0 ,  0, 0,  0};
    for(int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) board[i][j] = sub_board3[i][j];
    
    print_board(board);

    Position start3(1,3), end3(2,3);
    Move m3(start3,end3);

    vector<Position> vay_move3 = vay(board, m3, 1);
    cout<<vay_move3.size()<<"\n";
    act_move(board, m3, 1);*/

    return 0;
}

void copy_board(int** board_new, int** board)
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            board_new[i][j] = board[i][j];
}

vector<Position> ganh(int** board, Move m, int player){
    vector<Position> result;
    int enemy = player * -1;
    int x = m.pos_end.x, y = m.pos_end.y;

    if (x - 1 >= 0 && x + 1 <= 4)
    {
        if (board[x-1][y] == enemy && board[x+1][y] == enemy)
        {
            Position temp1(x-1,y), temp2(x+1,y);
            result.push_back(temp1);
            result.push_back(temp2);
        }
        if (y - 1 >= 0 && y + 1 <= 4){
            if (board[x+1][y+1] == enemy && board[x-1][y-1] == enemy){
                Position temp1(x+1,y+1), temp2(x-1,y-1);
                result.push_back(temp1);
                result.push_back(temp2);
            }
            if (board[x+1][y-1] == enemy && board[x-1][y+1] == enemy){
                Position temp1(x+1,y-1), temp2(x-1,y+1);
                result.push_back(temp1);
                result.push_back(temp2);
            }
        }
    }
    if (y - 1 >= 0 && y + 1 <= 4)
        if (board[x][y-1] == enemy && board[x][y+1] == enemy)
        {
            Position temp1(x,y-1), temp2(x,y+1);
            result.push_back(temp1);
            result.push_back(temp2);
        }
    return result;
}

vector<Position> adj(int** board, int** marked, Position pos, int player){
    int x = pos.x, y = pos.y;
    vector<Position> result;

    if (x - 1 >= 0)
        if (board[x-1][y] == player && marked[x-1][y] == 0){
            Position temp(x-1,y);
            result.push_back(temp);
        }
    if (x + 1 <= 4)
        if (board[x+1][y] == player && marked[x+1][y] == 0){
            Position temp(x+1,y);
            result.push_back(temp);
        }
    if (y - 1 >= 0)
        if (board[x][y-1] == player && marked[x][y-1] == 0){
            Position temp(x,y-1);
            result.push_back(temp);
        }
    if (y + 1 <= 4)
        if (board[x][y+1] == player && marked[x][y+1] == 0){
            Position temp(x,y+1);
            result.push_back(temp);
        }
    if (x + 1 <= 4 && y + 1 <= 4)
        if (board[x+1][y+1] == player && marked[x+1][y+1] == 0){
            Position temp(x+1,y+1);
            result.push_back(temp);
            }             

    if (x - 1 >= 0 && y + 1 <= 4)
        if (board[x-1][y+1] == player && marked[x-1][y+1] == 0){
            Position temp(x-1,y+1);
            result.push_back(temp);
            }            

    if (x - 1 >= 0 && y - 1 >= 0)
        if (board[x-1][y-1] == player && marked[x-1][y-1] == 0){
            Position temp(x-1,y-1);
            result.push_back(temp);
            }            
                        
    if (x + 1 <= 4 && y - 1 >= 0)
        if (board[x+1][y-1] == player && marked[x+1][y-1] == 0){
            Position temp(x+1,y-1);
            result.push_back(temp);
            }           
    return result;
}

bool check(int** board, Position pos){
    int i = pos.x, j = pos.y;
    if (i - 1 >= 0)
        if (board[i-1][j] != 1 && board[i-1][j] != -1) return true;

    if (i + 1 <= 4)
        if (board[i+1][j] != 1 && board[i+1][j] != -1) return true;

    if (j - 1 >= 0)
        if (board[i][j-1] != 1 && board[i][j-1] != -1) return true;

    if (j + 1 <= 4)
        if (board[i][j+1] != 1 && board[i][j+1] != -1) return true;

    if ((i + j) % 2 == 0)
    {
        if (i + 1 <= 4 && j + 1 <= 4)
            if (board[i+1][j+1] != 1 && board[i+1][j+1] != -1) return true;

        if (i - 1 >= 0 && j + 1 <= 4)
            if (board[i-1][j+1] != 1 && board[i-1][j+1] != -1) return true;

        if (i - 1 >= 0 && j - 1 >= 0)
            if (board[i-1][j-1] != 1 && board[i-1][j-1] != -1) return true;
                        
        if (i + 1 <= 4 && j - 1 >= 0)
            if (board[i+1][j-1] != 1 && board[i+1][j-1] != -1) return true;
    }
    return false;
}

bool chet(int** board, int** marked, Position pos){
    marked[pos.x][pos.y] = 1;
    if (check(board, pos)) return false;

    int player = board[pos.x][pos.y];

    vector<Position> ke = adj(board, marked, pos, player);
    if (ke.size() == 0) return true;

    for (unsigned int i = 0; i < ke.size(); i++) 
        if (!chet(board, marked, ke.at(i))) return false;
    
    return true;
}

int** init_marked(){
    int** marked = new int*[5];
    for(int i = 0; i < 5; i++)
    {
        marked[i] = new int[5];
        for (int j = 0; j < 5; j++) marked[i][j] = 0;
    }
    return marked;
}

void destroy_marked(int** marked){
    for (int i = 0; i < 5; i++)
        delete [] marked[i];
    delete [] marked;
}

vector<Position> vay(int** board, Move m, int player){
    int** new_board = copy_board(board);
    int enemy = player * -1;
    vector<Position> result;

    new_board[m.pos_start.x][m.pos_start.y] = 0;
    new_board[m.pos_end.x][m.pos_end.y] = player;

    vector<Position> ganh_move = ganh(board, m, player);
    for (unsigned int i = 0; i < ganh_move.size(); i++)
        new_board[ganh_move.at(i).x][ganh_move.at(i).y] = player;

    vector<Position> around;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (new_board[i][j] == enemy){
                Position temp(i,j);
                around.push_back(temp);
            }

    for (unsigned int i = 0; i < around.size(); i++)
        {
            Position pos = around.at(i);
            int** sub_marked = init_marked();
            if (chet(new_board, sub_marked, pos)) result.push_back(pos);
            destroy_marked(sub_marked);
        }

    return result;
}

vector<Position> Around(Position pos){
    vector<Position> result;
    int x = pos.x, y = pos.y;
       
    if (x - 1 >= 0){
        Position temp(x - 1, y);
        result.push_back(temp);
    }

    if (x + 1 <= 4){
        Position temp(x + 1, y);
        result.push_back(temp);
    }

    if (y - 1 >= 0){
        Position temp(x, y - 1);
        result.push_back(temp);
    }

    if (y + 1 <= 4){
        Position temp(x, y + 1);
        result.push_back(temp);
    }

    if ((x + y) % 2 == 0)
    {
        if ((x + 1 <= 4) && (y + 1 <= 4)){
            Position temp(x + 1, y + 1);
            result.push_back(temp);
        }

        if ((x - 1 >= 0) && (y + 1 <= 4)){
            Position temp(x - 1, y + 1);
            result.push_back(temp);
        }

        if ((x - 1 >= 0) && (y - 1 >= 0)){
            Position temp(x - 1, y - 1);
            result.push_back(temp);
        }

        if ((x + 1 <= 4) && (y - 1 >= 0)){
            Position temp(x + 1, y - 1);
            result.push_back(temp);
        }
    } 
    return result;
}

Move move_have_gone(int **current_board, int **previous_board, int player)
{
    Position start, end;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (previous_board[i][j] != current_board[i][j]) 
            {
                if (previous_board[i][j] == player)  { start.x = i; start.y = j; }
                else { end.x = i; end.y = j; }
            }
    return Move(start, end);
}

vector<Move> bay_or_mo(int **current_board, int **previous_board, int player){
    vector<Move> result;

    int current = 0, previous = 0;

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (current_board[i][j] == player) current++;
            else if (previous_board[i][j] == player) previous++;

    if (current != previous) return result;

    Move move_hg = move_have_gone(current_board, previous_board, player);

    vector<Position> around = Around(move_hg.pos_start);

    for (unsigned int i = 0; i < around.size(); i++)
    {
        if (current_board[around[i].x][around[i].y] == player)
        {
            Move y(around[i], move_hg.pos_start);
            vector<Position> ganh_temp = ganh(current_board, y, player);
            if (ganh_temp.size() > 0) result.push_back(y);
        }
    }
    return result;
}

void act_move(int** board, Move m, int player){
    vector<Position> ganh_move = ganh(board, m, player);
    vector<Position> vay_move = vay(board, m, player);

    for (int i = 0; i < ganh_move.size(); i++)
        board[ganh_move.at(i).x][ganh_move.at(i).y] = player;

    for (int i = 0; i < vay_move.size(); i++)
        board[vay_move.at(i).x][vay_move.at(i).y] = player;

    board[m.pos_start.x][m.pos_start.y] = 0;
    board[m.pos_end.x][m.pos_end.y] = player;
}

void act_move(int** board, int** previous_board, Move m, int player)
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            previous_board[i][j] = board[i][j];

    vector<Position> ganh_move = ganh(board, m, player);
    vector<Position> vay_move = vay(board, m, player);

    for (int i = 0; i < ganh_move.size(); i++)
        board[ganh_move.at(i).x][ganh_move.at(i).y] = player;

    for (int i = 0; i < vay_move.size(); i++)
        board[vay_move.at(i).x][vay_move.at(i).y] = player;

    board[m.pos_start.x][m.pos_start.y] = 0;
    board[m.pos_end.x][m.pos_end.y] = player;
}

vector<Move> get_valid_moves(int **current_board, int **previous_board, int player)
{
    vector<Move> trap = bay_or_mo(current_board, previous_board, player);

    if (trap.size() > 0) return trap;

    vector<Move> valid;

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (current_board[i][j] == player){
                Position start(i,j);

                if (i - 1 >= 0)
                    if (current_board[i-1][j] != 1 && current_board[i-1][j] != -1){
                        Position end(i-1,j);
                        Move temp(start,end);
                        valid.push_back(temp);
                    }

                if (i + 1 <= 4)
                    if (current_board[i+1][j] != 1 && current_board[i+1][j] != -1){
                        Position end(i+1,j);
                        Move temp(start,end);
                        valid.push_back(temp);
                    }

                if (j - 1 >= 0)
                    if (current_board[i][j-1] != 1 && current_board[i][j-1] != -1){
                        Position end(i,j-1);
                        Move temp(start,end);
                        valid.push_back(temp);
                    }

                if (j + 1 <= 4)
                    if (current_board[i][j+1] != 1 && current_board[i][j+1] != -1){
                        Position end(i,j+1);
                        Move temp(start,end);
                        valid.push_back(temp);
                    }

                if ((i + j) % 2 == 0)
                {
                    if (i + 1 <= 4 && j + 1 <= 4)
                        if (current_board[i+1][j+1] != 1 && current_board[i+1][j+1] != -1){
                            Position end(i+1,j+1);
                            Move temp(start,end);
                            valid.push_back(temp);
                        }

                    if (i - 1 >= 0 && j + 1 <= 4)
                        if (current_board[i-1][j+1] != 1 && current_board[i-1][j+1] != -1){
                            Position end(i-1,j+1);
                            Move temp(start,end);
                            valid.push_back(temp);
                        }

                    if (i - 1 >= 0 && j - 1 >= 0)
                        if (current_board[i-1][j-1] != 1 && current_board[i-1][j-1] != -1){
                            Position end(i-1,j-1);
                            Move temp(start,end);
                            valid.push_back(temp);
                        }
                        
                    if (i + 1 <= 4 && j - 1 >= 0)
                        if (current_board[i+1][j-1] != 1 && current_board[i+1][j-1] != -1){
                            Position end(i+1,j-1);
                            Move temp(start,end);
                            valid.push_back(temp);
                        }
                }
            }
    return valid;
}

int get_score(int **board, Move m, int player)
{
    int** new_board = copy_board(board);

    act_move(new_board, m, player);

    int player_old = 0, player_new = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
        {
            if (board[i][j] == player) player_old++;
            if (new_board[i][j] == player) player_new++;
        }
    return player_new - player_old;
}

int get_max_point_after(int** board, Move m, int player){
    int** new_board = copy_board(board);

    act_move(new_board, m, player);
    player = player * (-1);

    vector<Move> valid_move = get_valid_moves(new_board, board, player);
    vector<int> point;

    for (unsigned int i = 0; i < valid_move.size(); i++) 
        point.push_back(get_score(new_board, valid_move.at(i), player));   

    int max_point = point.at(0);
    for (unsigned int i = 1; i < point.size(); i++)
    {
        int score = get_score(new_board, valid_move.at(i), player);
        if (score > max_point)
            max_point = score;
    }

    return max_point;
}

Move select_move(int **current_board, int **previous_board, int player)
{
    vector<Move> valid_move = get_valid_moves(current_board, previous_board, player);
    vector<int> point;

    for (unsigned int i = 0; i < valid_move.size(); i++) 
        point.push_back(get_score(current_board, valid_move.at(i), player));

    vector<int> point_oracle;

    for (unsigned int i = 0; i < valid_move.size(); i++)
        point_oracle.push_back(get_max_point_after(current_board, valid_move.at(i), player));   

    vector<int> between;
    for (unsigned int i = 0; i <valid_move.size(); i++)
        between.push_back(point.at(i) - point_oracle.at(i));
    
    int best_move = 0;

    for (unsigned int i = 0; i < valid_move.size(); i++)
        if (between.at(i) > between.at(best_move)) best_move = i;
    
    return valid_move.at(best_move);
}

void play(int first)
{   
    clock_t start, end;
    double time_use;

    int count = 0, limit = 20;
    int player;
    if (first == 1) player = 1;
    else player = -1;

    int** current_board = init_board();
    int** previous_board = init_board();

    while (count < limit)
    {
        count++;
        vector<Move> valid_moves = get_valid_moves(current_board, previous_board, player);
        if (valid_moves.size() != 0)
        {
            if (player == 1)
            {
                start = clock();

                int** temp_current = copy_board(current_board);
                int** temp_previous = copy_board(previous_board);

                Move best_move = select_move(current_board, previous_board, player);

                copy_board(current_board, temp_current);
                copy_board(previous_board, temp_previous);

                act_move(current_board, previous_board, best_move, player);

                print_board(current_board);

                end = clock();
                time_use = (double)(end - start) / CLOCKS_PER_SEC;
                cout<<"Time use: "<<time_use<<"s\n";

                cout<<"--------------------\n";
                system("pause");
            }
            else {
                start = clock();

                srand (time(NULL));
                int index = rand()% valid_moves.size();
                Move new_move = valid_moves[index];
                act_move(current_board, previous_board, new_move, player);

                print_board(current_board);

                end = clock();
                time_use = (double)(end - start) / CLOCKS_PER_SEC;
                cout<<"Time use: "<<time_use<<"s\n";

                cout<<"--------------------\n";
                system("pause");
            }
        }
        else
            break;

        player *= -1;
    }
}