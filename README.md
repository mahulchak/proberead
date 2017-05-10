# proberead
A light weight utility program to extract long reads that span given genomic intervals

<i>Probem1</i> is a light weight program that takes output from a long or a short read aligner e.g.<i><a href="https://github.com/PacificBiosciences/blasr">BLASR</a></i>, <i><a href="http://bio-bwa.sourceforge.net/">bwa</a></i>, <i><a href="http://bowtie-bio.sourceforge.net/bowtie2/index.shtml">bowtie2</a></i> etc. and a space delimited genomic interval file to find reads that span each genomic interval. This can be used to find read coverage of a given region (for as many regions as you want). Subsequently, one could use this to validate called variants or assembly of a genomic region in a high throughput manner.

1. Compile the program

   You will need GNU c++ compiler that supports c++11. Compile like this -
   ```
      g++ -Wall -std=c++0x probem1.cpp -o probem1
   ```
 2. Generate alignment
    
    For simplicity, I am going to demonstrate how to work with the m1 output (see <i><a href="https://github.com/PacificBiosciences/blasr">BLASR</a></i> documentation for the details on m1 output format) from a <i>blasr</i> run. One can use any other alignment file format like sam. First, align the long reads to your assembly using <i>BLASR</i>.
   ```
      blasr reads.fasta assembly.fasta -bestn 1 -m 1 -nproc (# of cores) > foo.m1
   ```
   Here reads can be uncorrected raw reads or corrected reads from <i><a href="https://github.com/marbl/canu">canu</a></i> or <i><a href="https://github.com/PacificBiosciences/FALCON">Falcon</a></i> or <i><a href="https://github.com/xiaochuanle/MECAT">MECAT</a></i>.
    
 
 3. Process the inputs
 
    The alignment is processed using a simple <i>awk</i> command. The <i>awk</i> command generates a space delimited file with necessary alignment information. The example shown here is based on m1 alignment format, but can be created from any other alignment file. It is formatted like this -
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
