#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

// Enum for suits
enum class Suit { Hearts, Diamonds, Clubs, Spades };

// Card class
class Card {
public:
    int value;      // 1 to 13 (Ace to King)
    Suit suit;

    Card(int v, Suit s) : value(v), suit(s) {}

    // Return string for display
    string toString() const {
        const string values[] = { "A", "2", "3", "4", "5", "6", "7",
                                 "8", "9", "10", "J", "Q", "K" };
        const string suits[] = { "♥", "♦", "♣", "♠" };
        return values[value - 1] + suits[static_cast<int>(suit)];
    }

    // Check if two cards are the same color
    static bool isSameColor(const Card& c1, const Card& c2) {
        return ((c1.suit == Suit::Hearts || c1.suit == Suit::Diamonds) &&
            (c2.suit == Suit::Hearts || c2.suit == Suit::Diamonds)) ||
            ((c1.suit == Suit::Clubs || c1.suit == Suit::Spades) &&
                (c2.suit == Suit::Clubs || c2.suit == Suit::Spades));
    }
};

// Deck class (composition of cards)
class Deck {
protected:
    vector<Card> cards;

public:
    // Ordered constructor
    Deck() {
        for (int s = 0; s < 4; ++s) {
            for (int v = 1; v <= 13; ++v) {
                cards.emplace_back(v, static_cast<Suit>(s));
            }
        }
    }

    // Shuffle constructor
    static Deck createShuffledDeck() {
        Deck deck;
        shuffle(deck.cards.begin(), deck.cards.end(), default_random_engine(static_cast<unsigned>(time(0))));
        return deck;
    }

    void print() const {
        for (const auto& card : cards) {
            cout << card.toString() << " ";
        }
        cout << endl;
    }

    vector<Card>& getCards() {
        return cards;
    }
};

// Solitaire class (inherits from Deck)
class Solitaire : public Deck {
public:
    Solitaire() {
        cards = createShuffledDeck().getCards(); 
    }

    void play() {
        for (int pass = 1; pass <= 3; ++pass) {
            cout << "\nPass " << pass << ":\n";
            vector<Card> newCards;
            size_t i = 0;
            while (i + 2 < cards.size()) {
                Card& left = cards[i];
                Card& middle = cards[i + 1];
                Card& right = cards[i + 2];

                if (Card::isSameColor(left, right)) {
                    // Remove all three
                    i += 3;
                }
                else {
                    // Keep left
                    newCards.push_back(left);
                    ++i;
                }
            }
            // Add remaining cards
            while (i < cards.size()) {
                newCards.push_back(cards[i++]);
            }
            cards = newCards;
            print();
        }

        cout << "\nFinal number of cards: " << cards.size() << endl;
    }
};

// Main function
int main() {
    Solitaire game;
    cout << "Initial deck:\n";
    game.print();

    game.play();
    return 0;
}
