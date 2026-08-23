import java.util.Scanner;

public class CaesarCipher{
    public static String encrypt(String text, int shift)
    {
        StringBuilder result = new StringBuilder();

        for(char character : text.toCharArray()) //loop pela string
        {
            if(Character.isLetter(character)) //Caso seja letra
            {
                char base = Character.isLowerCase(character) ? 'a' : 'A'; //Vê se faz parte do alfabeto maiusculo ou minusculo

                char shifted = (char) ((character - base + shift) % 26 + base); //Calculo para saber a proxima letra do alfabeto pelo shift

                result.append(shifted); //Coloca na string nova encriptada
            }
            else
            {
                result.append(character);
            }
        }

        return result.toString();
    }

    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter text to encrypt: ");
        String inputText = scanner.nextLine();

        System.out.println("Enter shift key (0-25): ");
        int shiftKey = scanner.nextInt();

        String encrypted = encrypt(inputText, shiftKey);

        System.out.println("Encrypted text: " + encrypted);
    }
}