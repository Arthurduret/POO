#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <memory>
#include <array>    // Nouveau : pour gérer les tableaux constants de manière moderne
#include <utility>  // Pour std::move

// --- Définitions de Types pour la lisibilité ---
typedef float term_t;
typedef unsigned int exp_t;

// --- Namespace pour l'organisation du code (PB 4) ---
namespace MathExpression {

    // --- Fonctions utilitaires ---

    // Fonction pour l'opération de puissance (plus robuste)
    term_t power(term_t base, exp_t exp) {
        if (exp == 0) return 1.0f;
        if (exp == 1) return base;
        return std::pow(base, static_cast<float>(exp));
    }

    // Fonction utilitaire pour convertir un tableau C en std::array
    template <int N>
    std::array<exp_t, N> to_array(const exp_t c_array[N]) {
        std::array<exp_t, N> result;
        for (int i = 0; i < N; ++i) {
            result[i] = c_array[i];
        }
        return result;
    }

    // --- Classe de Base Abstraite ---
    template <int N>
    class Expression {
    public:
        // Toutes les opérations sont const (Immuabilité - PB 3)
        virtual term_t solve(const term_t vals[N]) const = 0;
        virtual std::unique_ptr<Expression<N>> differentiate(const exp_t mask[N]) const = 0;
        virtual std::unique_ptr<Expression<N>> clone() const = 0; // Copie Polymorphique (PB 3)
        virtual std::string toString() const = 0;
        virtual ~Expression() = default;
    };

    // --- Monomial (Terme) ---
    template <int N>
    class Monomial : public Expression<N> {
    protected:
        const term_t coeff;
        // Correction : Utilisation de std::array pour un membre constant
        const std::array<exp_t, N> exps;

    public:
        // Constructeur par défaut (Monôme nul)
        Monomial()
            : coeff(0.0f), exps() {} // exps() initialise le std::array à zéro

        // Constructeur pour une constante (ex: 5)
        Monomial(term_t coeff)
            : coeff(coeff), exps() {} // exps() initialise le std::array à zéro

        // Constructeur principal : utilise la fonction utilitaire dans la liste d'initialisation
        Monomial(term_t coeff, const exp_t exps_c_array[N])
            : coeff(coeff), exps(to_array<N>(exps_c_array)) {}

        // Méthode solve
        term_t solve(const term_t vals[N]) const override {
            term_t result = coeff;
            for (int i = 0; i < N; ++i) {
                result *= power(vals[i], exps[i]);
            }
            return result;
        }

        // Méthode differentiate (Retourne un NOUVEL objet Monomial - IMMUABILITÉ)
        std::unique_ptr<Expression<N>> differentiate(const exp_t mask[N]) const override {
            term_t newCoeff = coeff;
            exp_t newExps_c_array[N];
            bool isConstant = true;

            for (int i = 0; i < N; ++i) {
                newExps_c_array[i] = exps[i];
                if (mask[i] != 0 && exps[i] != 0) {
                    newCoeff *= exps[i];
                    newExps_c_array[i] -= 1;
                    isConstant = false;
                }
            }

            if (isConstant) {
                return std::make_unique<Monomial<N>>(0.0f);
            } else {
                return std::make_unique<Monomial<N>>(newCoeff, newExps_c_array);
            }
        }

        // Méthode clone (pour la copie polymorphique)
        std::unique_ptr<Expression<N>> clone() const override {
            // Ici on utilise directement le constructeur avec le tableau C interne
            return std::make_unique<Monomial<N>>(coeff, exps.data());
        }

        std::string toString() const override {
            if (coeff == 0.0f) return "0";
            std::string result = std::to_string(coeff);
            
            for (int i = 0; i < N; ++i) {
                if (exps[i] != 0) {
                    result += "x_" + std::to_string(i + 1);
                    if (exps[i] > 1) {
                         result += "^" + std::to_string(exps[i]);
                    }
                }
            }
            return result;
        }
    };

    // --- Polynomial (Polynôme) ---
    template <int N>
    class Polynomial : public Expression<N> {
    private:
        // Utilisation de std::vector et std::unique_ptr (PB 1 & PB 3)
        std::vector<std::unique_ptr<Expression<N>>> terms;

    public:
        // Constructeur prenant une liste de pointeurs uniques (transfert de propriété)
        Polynomial(std::vector<std::unique_ptr<Expression<N>>> initialTerms)
            : terms(std::move(initialTerms)) {}

        // Méthode solve
        term_t solve(const term_t vals[N]) const override {
            term_t result = 0.0f;
            for (const auto& term : terms) {
                result += term->solve(vals);
            }
            return result;
        }

        // Méthode differentiate (Retourne un NOUVEL objet Polynomial - IMMUABILITÉ)
        std::unique_ptr<Expression<N>> differentiate(const exp_t mask[N]) const override {
            std::vector<std::unique_ptr<Expression<N>>> derivedTerms;
            derivedTerms.reserve(terms.size());

            // Dérivation de chaque terme pour construire le nouveau Polynôme
            for (const auto& term : terms) {
                derivedTerms.push_back(term->differentiate(mask));
            }

            // Retourne un nouveau Polynomial
            return std::make_unique<Polynomial<N>>(std::move(derivedTerms));
        }

        // Méthode clone
        std::unique_ptr<Expression<N>> clone() const override {
            std::vector<std::unique_ptr<Expression<N>>> clonedTerms;
            clonedTerms.reserve(terms.size());

            for (const auto& term : terms) {
                // Appel de la méthode clone() polymorphique (Virtual Clone)
                clonedTerms.push_back(term->clone());
            }
            return std::make_unique<Polynomial<N>>(std::move(clonedTerms));
        }

        std::string toString() const override {
            std::string result = "";
            bool first = true;

            for (const auto& term : terms) {
                std::string termStr = term->toString();
                if (termStr != "0") {
                    // Logique d'affichage simplifiée
                    if (!first && termStr.front() != '-') {
                        result += " + ";
                    } else if (!first && termStr.front() == '-') {
                        // Supprime l'espace avant le signe moins
                        result += " ";
                    }
                    result += termStr;
                    first = false;
                }
            }
            return result.empty() ? "0" : result;
        }
    };
} // Fin du namespace MathExpression

// --- Exemple d'utilisation dans main ---

int main() {
    using namespace std;
    using namespace MathExpression;

    const int N = 1;
    term_t vals[N] = {3.0f};
    const exp_t exps_x2[N] = {2u};
    const exp_t exps_x1[N] = {1u};
    exp_t mask[N] = {1u}; // Dérivation par rapport à x_1

    cout << "### Démonstration d'Immuabilité (PB 3) ###" << endl;

    // Monôme : 12.4x^2
    Monomial<N> m1(12.4f, exps_x2);
    cout << "1. Monomial m1 original: " << m1.toString() << endl;

    // Dérivation: retourne un NOUVEL objet (pointeur unique)
    unique_ptr<Expression<N>> dm1 = m1.differentiate(mask);
    cout << "2. Derivee de m1 (dm1): " << dm1->toString() << endl; // 24.8x

    cout << "3. m1 original apres primitive: " << m1.toString() << " (Prouve l'immuabilité)" << endl;

    cout << "\n### Démonstration de Polynôme (PB 1) ###" << endl;

    // Création des termes et transfert de propriété (gestion memoire RAII)
    vector<unique_ptr<Expression<N>>> terms;
    terms.push_back(make_unique<Monomial<N>>(5.0f));           // 5 (constante)
    terms.push_back(make_unique<Monomial<N>>(18.0f, exps_x1)); // 18x
    terms.push_back(make_unique<Monomial<N>>(12.4f, exps_x2)); // 12.4x^2

    // Polynôme : P(x) = 5 + 18x + 12.4x^2
    Polynomial<N> p1(std::move(terms));
    cout << "4. Polynome P(x): " << p1.toString() << endl;
    cout << "5. P(" << vals[0] << ") = " << p1.solve(vals) << endl;

    // Dérivation du Polynôme (retourne un NOUVEL objet)
    unique_ptr<Expression<N>> dp1 = p1.differentiate(mask);
    
    cout << "6. Derivee P'(x): " << dp1->toString() << endl; // 18 + 24.8x
    cout << "7. P'(" << vals[0] << ") = " << dp1->solve(vals) << endl; // 18 + 24.8 * 3 = 92.4

    return 0;
}