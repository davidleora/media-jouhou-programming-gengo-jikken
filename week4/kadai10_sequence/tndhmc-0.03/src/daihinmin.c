#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "common.h"

void print_info_table(int info_table[8][15]) {
    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 15; j++) {
            printf("%d ", info_table[i][j]);
        }
        printf("\n");
    }
}

void search_low_card(int out_cards[8][15], int my_cards[8][15], int use_joker_flag)
{
  /*
    低い方から探して,最初に見つけたカードを一枚out_cardsにのせる。
    use_joker_flagが1のとき,カードが見つからなければ,jokerを一枚out_cardsにのせる。
  */
  int i, j, find_flag = 0;

  clear_table(out_cards); // テーブルをクリア
  for (j = 1; j < 14 && find_flag == 0; j++)
  { // 低い方からさがし
    for (i = 0; i < 4 && find_flag == 0; i++)
    {
      if (my_cards[i][j] == 1)
      {                                   // カードを見つけたら
        find_flag = 1;                    // フラグを立て
        out_cards[i][j] = my_cards[i][j]; // out_cardsにのせ,ループを抜ける。
      }
    }
  }
  if (find_flag == 0 && use_joker_flag == 1)
  {                       // 見つからなかったとき
    out_cards[0][14] = 2; // ジョーカーをのせる
  }
}

void search_low_card_wosp(int out_cards[8][15], int my_cards[8][15], int info_table[8][15], int use_joker_flag){
  int i, j, find_flag = 0;

  clear_table(out_cards);
  for (j = 1; j < 14 && find_flag == 0; j++)
  {
    for (i = 0; i < 4 && find_flag == 0; i++)
    {
      if (my_cards[i][j] == 1 && info_table[4][j] == 1)
      {
        find_flag = 1;
        out_cards[i][j] = my_cards[i][j];
      }
    }
  }
  if (find_flag == 0 && use_joker_flag == 1)
  {
    out_cards[0][14] = 2;
  }
}

void make_info_table(int info_table[8][15], int info_j_table[8][15], int my_cards[8][15])
{
  int i, j;
  int joker_last_position;
  clear_table(info_table);
  clear_table(info_j_table);
  for (i = 0; i < 4; i++)
  {
    joker_last_position = 15;
    for (j = 13; j > 0; j--)
    {
      if(my_cards[i][j] == 1){
        info_table[i][j] = info_table[i][j+1] + 1;
        info_j_table[i][j] = info_j_table[i][j+1] + 1;
      }
      else if(my_cards[i][j] == 0){
        info_table[i][j] = 0;
        info_j_table[i][j] = joker_last_position - j;
        joker_last_position = j;
      }
    }
  }

  for (i = 0; i < 4; i++)
  {
    for (j = 1; j < 14; j++)
    {
      if(info_table[i][j] == 2){
        info_table[i][j] = 1;
      }
      if(info_j_table[i][j] == 2){
        info_j_table[i][j] = 1;
      }
    }
  }

  for (i = 1; i <= 13; i++)
  {
    info_table[4][i] = my_cards[0][i] + my_cards[1][i] + my_cards[2][i] + my_cards[3][i];
  }

  if (my_cards[4][1] == 2){
    for(i = 1; i <= 14; i++){
      info_j_table[4][i] = info_table[4][i] + 1;
    }
  }
  else {
    for(i = 1; i <= 14; i++){
      info_j_table[4][i] = info_table[4][i];
    }
  }
}

int search_low_pair(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15])
{
  int i, j;
  clear_table(dst_cards);
  for (i = 1; i <= 13; i++)
  {
    if (info_table[4][i] >= 2)
      break;
  }
  if (i <= 13)
  {
    for (j = 0; j <= 3; j++)
      dst_cards[j][i] = my_cards[j][i];
      print_info_table(dst_cards);
    return 1;
  }
  else
    return 0;
}

int search_low_pair_wj(int dst_cards[8][15], int info_j_table[8][15], int my_cards[8][15]){
  int i, j, k;
  int sum;
  clear_table(dst_cards);
  for (i = 1; i < 14; i++){
    if(info_j_table[4][i] >= 2){
      sum = 0;
      for(j=0; j<4; j++){
        sum += my_cards[j][i];
      }
      while(sum < info_j_table[4][i]){
        for(k=0; k<4; k++){
          if(my_cards[k][i] == 0){
            dst_cards[k][i] = 2;
            sum++;
            break;
          }
        }
      }
      break;
    }
  }
  if(i <= 13){
    for(j=0; j <=3; j++){
      if(dst_cards[j][i] != 2)
        dst_cards[j][i] = my_cards[j][i];
    }
    print_info_table(dst_cards);
    return 1;
  }
  else
    return 0;
}

int search_low_sequence(int dst_cards[8][15], int info_table[8][15])
{
  int i, j, k;
  int search_flag = 0;
  clear_table(dst_cards);
  for (i=1; i<=13; i++)
  {
    for (j=0; j<4; j++)
    {
      if (info_table[j][i] >= 3) {
        search_flag = 1;
        break;
      }
    }
    if (search_flag == 1) break;
  }
  if (i<=13){
    for(k=0; k<info_table[j][i]; k++){
      dst_cards[j][i+k] = 1;
    }
    print_info_table(dst_cards);
  }
  return 0;
}

int search_low_sequence_wj(int dst_cards[8][15], int info_j_table[8][15], int my_cards[8][15]){
  int i, j, k;
  int search_flag = 0;
  clear_table(dst_cards);
  for (i=1; i<=13; i++)
  {
    for (j=0; j<4; j++)
    {
      if(info_j_table[j][i] >= 3){
        search_flag = 1;
        break;
      }
    }
    if (search_flag == 1) break;
  }
  if (i <= 13){
    for(k=0; k<info_j_table[j][i]; k++){
      if(my_cards[j][i+k] == 0){
        dst_cards[j][i+k] = 2;
      }
      else {
        dst_cards[j][i+k] = 1;
      }
    }
    return 1;
  } else {
    return 0;
  }
}