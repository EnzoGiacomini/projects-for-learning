import javax.swing.*;

public class WeatherConverter{

    public static double fToCelcius(double farrenheit)
    {
        double celcius = (farrenheit - 32)/1.8;

        return celcius;
    }

    public static void main(String[] args)
    {
        JFrame frame = new JFrame("Weather Converter");
        frame.setSize(300,  150);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(null);

        frame.setVisible(true);

        JTextField textField = new JTextField();
        textField.setBounds(20, 20, 150, 25);

        JButton button = new JButton("Convert");
        button.setBounds(180, 20, 90, 25);

        JLabel label = new JLabel("Celcius = ");
        label.setBounds(20, 60, 250, 25);

        frame.add(textField);
        frame.add(button);
        frame.add(label);

        button.addActionListener(e -> {
            double farrenheit = Double.parseDouble( textField.getText());
            label.setText("Celcius = " + fToCelcius(farrenheit));
        });
    }
}