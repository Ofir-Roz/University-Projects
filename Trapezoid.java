/*
 * Trapezoid
 * @author: Ofir Rozanes.
 * @Date: 04/04/2020
 * This program calculates the area and the perimeter of a trapezoid on the 2-dimensional space.
 * The program takes the following parameters from the user:
 * 1)the left point coordinates, and the length of the first base (compare to X axis).
 * 2)the left point coordinates, and the length of the second base (compare to X axis).
 */
import java.util.Scanner;
public class Trapezoid
{
    public static void main(String [] args)
    {
        int xA, yA,xB, yB, xC, yC, xD, yD, lengthA, lengthD, height;
        double distanceAD, distanceCB, area, perimeter;

        System.out.println("\n-----------------------------\n" +
                "\nHello and Welcome." +
                "\nThis program calculates the area and the perimeter of a trapezoid" +
                " on the 2-dimensional space.");
        //Now we take the parameters.
        System.out.println("\nPlease enter the left point coordinates [(x,y)]" +
                "of the base followed by its length:");
        Scanner scan = new Scanner(System.in);
        xA = scan.nextInt();
        yA = scan.nextInt();
        lengthA = scan.nextInt();
        System.out.println("Please enter the left point coordinates [(x,y)]" +
                "of the other base followed by its length:");
        xD = scan.nextInt();
        yD = scan.nextInt();
        lengthD = scan.nextInt();

        //Now to find the other points.
        xB = xA + lengthA;
        yB = yA;
        xC = xD + lengthD;
        yC = yD;

        //Calculate the perimeter.
        distanceAD = Math.abs(Math.sqrt(Math.pow(xA-xD,2) + Math.pow(yA-yD,2)));
        distanceCB = Math.abs(Math.sqrt(Math.pow(xC-xB,2) + Math.pow(yC-yB,2)));
        perimeter=lengthA + distanceCB + lengthD + distanceAD;

        //Calculate the area.
        height = Math.abs(yD-yA);
        area = (height*(lengthA+lengthD))/2.0;

        //The results.
        System.out.println("The area of the trapezoid is " + area);
        System.out.println("The perimeter of the trapezoid is " + perimeter);
    }//End of main.
}//End of Trapezoid.
