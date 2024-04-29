#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DECK_SIZE 52
#define FACE_CARDS 10


void print_instructions() {
    printf("Welcome to the Blackjack game!\n");
    printf("Instructions:\n");
    printf("1. You will start with $100.\n");
    printf("2. Place your bet to start the game.\n");
    printf("3. You will be dealt two cards.\n");
    printf("4. The dealer will also be dealt two cards, but one card will be face down.\n");
    printf("5. Your goal is to get a hand value as close to 21 as possible without exceeding it.\n");
    printf("6. You can 'Hit' to receive another card or 'Stand' to keep your current hand.\n");
    printf("7. If you think your hand is strong enough, you can 'Double Down' to double your bet and receive one more card.\n");
    printf("8. After you stand, the dealer will reveal their facedown card and draw cards until their hand value is 17 or higher.\n");
    printf("9. If your hand value is higher than the dealer's or if the dealer busts, you win!\n");
    printf("10. If your hand value is lower than the dealer's or if you bust, you lose.\n");
    printf("11. A tie results in a push, and you get your bet back.\n");
    printf("12. The game continues until you run out of money or choose to quit.\n");
    printf("\nLet's begin!\n");
}

char *faces[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
char *suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};

char *symbols[] = {
    "┌─────────┐\n│         │\n│    ♥    │\n│         │\n│         │\n└─────────┘",
    "┌─────────┐\n│         │\n│    ♦    │\n│         │\n│         │\n└─────────┘",
    "┌─────────┐\n│         │\n│    ♣    │\n│         │\n│         │\n└─────────┘",
    "┌─────────┐\n│         │\n│    ♠    │\n│         │\n│         │\n└─────────┘"
};

int get_card_value(int card) {
    int value = (card % 13) + 1;
    if (value > 10)
        value = FACE_CARDS;
    return value;
}

void print_card(int card) {
    int face_index = card % 13;
    int suit_index = card / 13;
    printf("┌─────────┐\n│ %s       │\n│         │\n│    %s    │\n│         │\n│       %s │\n└─────────┘\n",
           faces[face_index], suits[suit_index], faces[face_index]);
}

int main() {
    srand(time(NULL));
    
    print_instructions(); 
    int deck[DECK_SIZE];
    for (int i = 0; i < DECK_SIZE; i++) {
        deck[i] = i;
    }

    // Shuffle the deck
    for (int i = 0; i < DECK_SIZE; i++) {
        int j = rand() % DECK_SIZE;
        int temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }

    int player_money = 100; // Player's initial money
    int bet;

    
    // Main game loop
    while (player_money > 0) {
        printf("You have $%d.\n", player_money);
        printf("Enter your bet (or 0 to quit): ");
        scanf("%d", &bet);

        if (bet == 0) {
            printf("Thanks for playing!\n");
            break;
        }

        if (bet > player_money) {
            printf("You don't have enough money to bet that amount.\n");
            continue;
        }

        // Deal two cards to the player
        int player_hand[10]; // Array to store player's cards
        int player_hand_size = 0;
        player_hand[player_hand_size++] = deck[0];
        player_hand[player_hand_size++] = deck[1];
        printf("Your cards:\n");
        print_card(player_hand[0]);
        print_card(player_hand[1]);

        // Calculate total value of player's hand
        int player_total = get_card_value(player_hand[0]) + get_card_value(player_hand[1]);
        printf("Total: %d\n", player_total);

        // Main game loop for player's turn
        char choice;
        while (1) {
            printf("Hit (h), Stand (s), or Double Down (d): ");
            scanf(" %c", &choice);

            if (choice == 'h') {
                // Draw another card
                player_hand[player_hand_size++] = deck[player_hand_size + 1];
                printf("Your new card:\n");
                print_card(player_hand[player_hand_size - 1]);
                player_total += get_card_value(player_hand[player_hand_size - 1]);
                printf("Total: %d\n", player_total);

                // Check if player busts
                if (player_total > 21) {
                    printf("Bust! You lose $%d.\n", bet);
                    player_money -= bet;
                    break;
                }
            } else if (choice == 's') {
                // Player stands, dealer's turn
                printf("Dealer's turn:\n");

                // Dealer draws cards until the total is 17 or higher
                int dealer_hand[10]; // Array to store dealer's cards
                int dealer_hand_size = 0;
                dealer_hand[dealer_hand_size++] = deck[2];
                dealer_hand[dealer_hand_size++] = deck[3];
                printf("Dealer's cards:\n");
                print_card(dealer_hand[0]);
                print_card(dealer_hand[1]);
                int dealer_total = get_card_value(dealer_hand[0]) + get_card_value(dealer_hand[1]);

                while (dealer_total < 17) {
                    dealer_hand[dealer_hand_size++] = deck[dealer_hand_size + 3];
                    printf("Dealer draws another card:\n");
                    print_card(dealer_hand[dealer_hand_size - 1]);
                    dealer_total += get_card_value(dealer_hand[dealer_hand_size - 1]);
                }

                printf("Dealer's Total: %d\n", dealer_total);

                // Determine the winner
                if (dealer_total > 21 || dealer_total < player_total) {
                    printf("You win $%d!\n", bet);
                    player_money += bet;
                } else if (dealer_total > player_total) {
                    printf("Dealer wins. You lose $%d.\n", bet);
                    player_money -= bet;
                } else {
                    printf("It's a tie. You get back $%d.\n", bet);
                }

                break;
            } else if (choice == 'd') {
                // Double down
                bet *= 2;

                // Draw one more card
                player_hand[player_hand_size++] = deck[player_hand_size + 1];
                printf("Your new card:\n");
                print_card(player_hand[player_hand_size - 1]);
                player_total += get_card_value(player_hand[player_hand_size - 1]);
                printf("Total: %d\n", player_total);

                // Check if player busts
                if (player_total > 21) {
                    printf("Bust! You lose $%d.\n", bet);
                    player_money -= bet;
                    break;
                }

                // Player stands, dealer's turn
                printf("Dealer's turn:\n");

                // Dealer draws cards until the total is 17 or higher
                int dealer_hand[10]; // Array to store dealer's cards
                int dealer_hand_size = 0;
                dealer_hand[dealer_hand_size++] = deck[2];
                dealer_hand[dealer_hand_size++] = deck[3];
                printf("Dealer's cards:\n");
                print_card(dealer_hand[0]);
                print_card(dealer_hand[1]);
                int dealer_total = get_card_value(dealer_hand[0]) + get_card_value(dealer_hand[1]);

                while (dealer_total < 17) {
                    dealer_hand[dealer_hand_size++] = deck[dealer_hand_size + 3];
                    printf("Dealer draws another card:\n");
                    print_card(dealer_hand[dealer_hand_size - 1]);
                    dealer_total += get_card_value(dealer_hand[dealer_hand_size - 1]);
                }

                printf("Dealer's Total: %d\n", dealer_total);

                // Determine the winner
                if (dealer_total > 21 || dealer_total < player_total) {
                    printf("You win $%d!\n", bet);
                    player_money += bet;
                } else if (dealer_total > player_total) {
                    printf("Dealer wins. You lose $%d.\n", bet);
                    player_money -= bet;
                } else {
                    printf("It's a tie. You get back $%d.\n", bet);
                }

                break;
            } else {
                printf("Invalid choice. Please enter 'h' for Hit, 's' for Stand, or 'd' for Double Down.\n");
            }
        }
    }

    if (player_money <= 0) {
        printf("You've run out of money. Better luck next time!\n");
    }

    return 0;
}
