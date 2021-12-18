/*
 * Petrol.
 * @author: Ofir Rozanes.
 * @Date: 28/03/2020.
 * This program converts the fuel consumption of a car from miles per gallon to litres per 100km.
 * The program gets the following parameter from the user : miles per gallon.
 * Then calculates the result.
 */
import java.util.Scanner;
public class Petrol
{
    public static void main (String  [] args)
    {
        final int MAX = 100;
        final double LITRES_IN_GALLON = 3.785;
        final double KM_IN_MILES = 1.609;
        Scanner scan = new Scanner(System.in);

        System.out.println("\n-----------------------------\n" +
                "\nHello and Welcome.\nThis is a car petrol converter.");
        System.out.println("Please enter the car's petrol consumption "+
                "measured in miles per gallon:");

        double milesPerGallon = scan.nextDouble();
        double milesPerLitres = milesPerGallon/LITRES_IN_GALLON;
        double kmPerLitres = milesPerLitres*KM_IN_MILES;
        double litresPer100Km = MAX/kmPerLitres;

        double afterRounding = Math.round(litresPer100Km*MAX)/(MAX*1.0);

        System.out.println("The car's petrol consumption converted to litres/100km is:\n" +
                afterRounding);
        System.out.println("\n-End-");
    } // End of method main
} //End of class Petrol