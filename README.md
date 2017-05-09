# Fetch-long-reads-mapping-to-an-interval
A light weight utility program to extract long reads that span given genomic intervals

<i>Probem1</i> is a light weight program that takes a <i><a href="https://github.com/PacificBiosciences/blasr">BLASR</a></i> alignment output and a space delimited genomic interval file to find reads that span each genomic interval. This can be used to find read coverage of a given region (for as many regions as you want). Subsequently, one could use this to validate called variants in a high throughput manner.

1. Compile the program

   You will need GNU c++ compiler that supports c++11. Compile like this -
   ```
      g++ -Wall -std=c++0x probem1.cpp -o probem1
   ```
 2. Process the inputs
 
    For simplicity, the m1 output (see <i><a href="https://github.com/PacificBiosciences/blasr">BLASR</a></i> documentation for the details on m1 output format) from the <i>blasr</i> run is formatted like this -
    ```
       awk '{print $1" "$2" "$7" "$8" "$12}' foo.m1 > foo.filtered.m1
    ```
    The genomic interval file should look like this -
    ```
       chr1 100 200
       chr2 300 400
    ```
  3. Run <i>probem1</i>
  
     <i> Probem1 </i>is run like this -
     ```
        probem1 foo.filtered.m1 foo.interval.txt > output_reads
     ```
     
     The output has the following space delimited format -
     ```
        Chrom_Name Chrom_Start Chrom_End Read_Name Alignment_Start Alignment_End
     ```
     
     Citation for <i>Probem1</i> is <a href="http://biorxiv.org/content/early/2017/03/08/114967">here</a>.
