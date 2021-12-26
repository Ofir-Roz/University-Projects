import java.util.Scanner;
import java.io.File;
import java.io.*;
import java.io.FileNotFoundException;

/**
 * Class HashTable.
 * @author Ofir Rozanes
 * @version 14/01/2021
 *
 * This class implement a Hash Table with Hash functions using MurmurHash class of Viliam Holub (public domain).
 * To use the program please put all the files (including the text files) in the same directory.
 * ENJOY!
 */
public class HashTable
{
    /**
     * The main function.
     * Running all the sub-methods to build and check the Hash-Table.
     *
     * Runs on O(k(n+l)+m) time complexity (Theta is more right).
     * M for build and set the table array to 0, O(kn) to fill the table,
     * O(kl) to search in the table.
     */
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_CYAN = "\u001B[36m";

    public static void main(String [] args) {
        try
        {
            Scanner scan=new Scanner(System.in);
            //getting the data from the user and building the arrays.
            int m=getM(scan);
            int k=getK(scan);
            int[] arrM=new int[m];//In Java all the array values are set to 0 at the declaration. O(m)?
            int[] hashArr=new int[k];

            fileBuilder(scan, arrM, hashArr);//To fill the hash table. Runs on O(kn) (n for the num of strings).
            //To search in the table for a string. Runs on O(kl) (l for the num of string to check)
            fileChecker(scan, arrM, hashArr);

            ifShowTheTable(scan, arrM);//use it only if the table is smaller than 64.
        }

        catch(IOException e)
        {
            System.err.println("Caught IOException : " + e.getMessage());
        }
    }

    /**
     * getK return k the number of different hash functions.
     * @param scan to scan the keyboard.
     * @return k the number of different hash functions.
     */
    private static int getK(Scanner scan) {
        int k;
        System.out.print("Enter your k:");
        k = scan.nextInt();
        System.out.println("Number of different hash functions:"+k+"\n");
        return k;
    }

    /**
     * getM m the length of the Hash Table.
     * @param scan to scan the keyboard.
     * @return m the length of the Hash Table.
     */
    private static int getM(Scanner scan) {
        int m;
        System.out.println(
                "\n\t-*-*-\t\t-*-*-\t\t-*-*-\t\t-*-*-\t\t-*-*-\t\t-*-*-\t"+
                "\n\t\tHello and Welcome to the Hash Table program\n"+
                "\t-*-*-\t\t-*-*-\t\t-*-*-\t\t-*-*-\t\t-*-*-\t\t-*-*-\t\n\n"+
                "The program takes a text file from the user and puts all the strings inside (separates by commas)\n"+
                "and put it into a hash table.\n"+
                "After that the program can check if some strings are inside.\n"+
                "Enjoy your using.\n");

        System.out.print("Enter your m (the size of the Hash-Table):");
        m = scan.nextInt();
        System.out.println("the length of the table is:"+ m);
        return m;
    }

    /**
     * ifShowTheTable check if the user want to see the table.
     * @param scan to scan the user answer.
     * @param arrM to build the table from.
     */
    private static void ifShowTheTable(Scanner scan, int[] arrM) {
        String answer;
        System.out.print("Before we end the program, do you want to see the HashTable? (y/n) ");
        answer=scan.next();
        if (answer.equals("y")||answer.equals("Y"))
            bitTableLook(arrM);
    }

    /**
     * hashCreator this function build and fill the hash table.
     * @param hashArr the “k” different hash functions.
     * @param arrM to fill the table array.
     * @param str the string to encrypt.
     */
    public static void hashCreator(int[] hashArr, int[] arrM, String str)
    {
        buildHashArr(hashArr, str);//to make different k functions.
        int mod;

        //here we insert the hash number to the table using modulo.
        for (int j : hashArr) {
            mod=Math.abs(j%arrM.length);
            arrM[mod]=1;
        }
    }

    /**
     * hashChecker this function check if a string is in the hash table.
     * @param hashArr the “k” different hash functions.
     * @param arrM to check the table array.
     * @param str the string to check.
     */
    public static void hashChecker(int[] hashArr, int[] arrM, String str)
    {
        buildHashArr(hashArr, str);//to make different k functions.

        int mod;

        //Now we check if all the correct indexes is set to 1.
        //Using flag to indicate if the cell is set to 0.
        boolean flag=true;
        for (int j : hashArr) {
            mod=Math.abs(j%arrM.length);
            if (arrM[mod]==0) {
                flag=false;
            }
        }

        //printing the right answer.
        System.out.print(str);
        if (flag)
            System.out.println(" - "+"yes");
        else
            System.out.println(" - "+"no");
        System.out.println("------------");
    }

    /**
     * buildHashArr a function to build an array of the different hash numbers.
     * @param hashArr to fill the array.
     * @param str the string to encrypt.
     */
    private static void buildHashArr(int[] hashArr, String str) {
        for (int i=0; i<hashArr.length; i++)
        {
            //call to hash32 function from MurmurHash class to get unique hash number.
            hashArr[i]=MurmurHash.hash32(str.getBytes(),str.length()-1,i);
        }
    }

    /**
     * fileBuilder a function to load the insertion file.
     * @param scan for scanning the file name.
     * @param arrM to send in the different strings from the file (separated with “,").
     * @param hashArr to sent in the different hash function array.
     * @throws FileNotFoundException if there is no file
     */
    private static void fileBuilder(Scanner scan, int[] arrM, int[] hashArr) throws FileNotFoundException
    {
        System.out.print("Enter your Insert file:");
        String file_name;
        file_name= scan.next();
        File text = new File(file_name+".txt");//a file object for the local file.
        
        Scanner myReader = new Scanner(text);// to scan the string inside the file.
        while (myReader.hasNextLine())//going all the way to the EOF
        {
            String str = myReader.nextLine();

            String[] words = str.split(",");//here we separate the lines to strings.

            for (String word : words) {//sending the strings one by one.
                hashCreator(hashArr, arrM, word);
            }
        }
        myReader.close();
    }

    /**
     * fileChecker this function search in a given file if a string is already in the hash table.
     * @param scan for scanning the file name.
     * @param arrM to send in the different strings from the file (separated with ",").
     * @param hashArr to sent in the different hash function array.
     * @throws FileNotFoundException if there is no file
     */
    private static void fileChecker(Scanner scan, int[] arrM, int[] hashArr) throws FileNotFoundException
    {
        System.out.print("\nHow many check files do you have? Please enter a number:");
        int numOfFiles= scan.nextInt();

        for (int i=0;i<numOfFiles;i++)//to check few files.
        {
            System.out.print("\nEnter the name of the file:");
            String file_name;
            Scanner myReader;
            file_name=scan.next();
            File myTest1=new File(file_name+".txt");//a file object for the local file.
            System.out.println("\n\n------Is the string inside?-----\n");
            myReader=new Scanner(myTest1);//to scan the string inside the file.
            while (myReader.hasNextLine())//going all the way to the EOF
            {
                String str=myReader.nextLine();

                String[] words=str.split(",");//here we separate the lines to strings.

                for (String word : words) {//sending the strings one by one.
                    hashChecker(hashArr, arrM, word);
                }
            }
            System.out.println();
            myReader.close();
        }
    }

    /**
     * bitTableLook this function show a representation of the hash table in the terminal.
     * If the Table is big do not use it (over 64 bits).
     * @param arrM the hash array to build from.
     */
    private static void bitTableLook(int[] arrM)
    {
        System.out.println(ANSI_CYAN+"\n\n---Image Of the Table---\n"+ANSI_RESET);
        System.out.println("\t----------------------------------------------------------------------------------------------\n");
        System.out.print("Indices: ");
        for (int i=0; i<arrM.length; i++)
        {
            if (i%30==0&&i!=0)
                System.out.print(ANSI_GREEN+"\n\t\t -----------------------------------------------------" +
                        "-------------------------" +
                        "-----------------------------------------------------------------------\n\t\t "+ANSI_RESET);
            if (i<10)
                System.out.print(ANSI_GREEN+"0"+i+" | "+ANSI_RESET);
            else
                System.out.print(ANSI_GREEN+i+" | "+ANSI_RESET);
        }
        System.out.println();
        System.out.println("\t----------------------------------------------------------------------------------------------");
        System.out.print("On/Off:  ");
        for (int i=0; i<arrM.length; i++)
        {
            if (i%30==0&&i!=0)
                System.out.print(ANSI_GREEN+"\n\t\t ------------------------------------------" +
                        "------------------------------------------------------" +
                        "-----------------------------------------------------\n\t\t "+ANSI_RESET);
            System.out.print(ANSI_GREEN+" "+arrM[i]+" | "+ANSI_RESET);
        }
        System.out.println("\n----------------------------------------------------------------------------------------------");
    }

}
