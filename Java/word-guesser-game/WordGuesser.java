import java.util.Scanner;

public class WordGuesser {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String word = "GRÊMIO";
        String attempt = " ";
        int maxAttempts = 5, attempts = 0;

        System.out.println("Welcome to the Word Guesser Game!");
        System.out.println("You have 5 attempts remaining to guess the secret word: _ _ _ _ _ _");

        while(attempts < maxAttempts)
        {
            System.out.println((attempts + 1) + " attempt: ");
            attempt = scanner.nextLine();

            if(attempt.trim().toUpperCase().equals(word))
            {
                System.out.println("Correct!");
                break;
            }
            else
            {
                attempts++;
                System.out.println("Incorrect! You have " + (maxAttempts - attempts) + " remaining.");
            }
        }
    }
}
