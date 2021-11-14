
#ifndef __LEARN_THE_FILE_H__
#define __LEARN_THE_FILE_H__
#include "PrintToFile.h"


#include <iostream>
#include <fstream>
#include <list>
#include <map>


class LearnTheFile
{
public:

    std::string  EXCLUSIVE_WORD[6]{
        "THE" ,
        "IS",
        "ARE",
        "WAS",
        "AM",
        "A",

    };

    LearnTheFile(std::string a_name_of_file, std::string a_name_output_file);
    ~LearnTheFile() {}

    int GetNumofLines() { return m_number_of_lines; }   //Q1
    int GetNumOfWords() { return m_number_of_words; }   //Q2
    
    void PrintAllWords();
    void PrintAllUniqWords();   //Q3

    int GetNumberOfPhrases() { return m_number_of_phrases; }
    int GetNumberfLetters() { return m_number_of_letters; }

    float GetAvrgLenghtOfPhrase() { return (float(m_count_the_chars_from_all_phrases) / m_number_of_phrases); } //Q4
    int GetNumOfMostLongPhrase() { return m_most_long_phrase; }//Q4

    std::string GetMostPopularWord() { return m_most_popular_word; }//Q5    
    std::string GetMostPopularWordExclusive() { return m_most_popular_word_exclusiv; }//Q5

    int GetTheLongPhraseWithoutK() { return m_most_long_phrase_without_k; }  //Q6
   
    //float GetAvrgLenght() { return ((m_count_the_chars_from_all_phrases/m_number_of_phrases)); }//NO
    std::string GetMostLongWord() { return m_most_long_word; }//NO
    void makeFileRequests(); //Q


    LearnTheFile() { };
protected:
    std::ifstream m_file;
    
private:
    void FindNumOfLines();  //1
    void FindNumOfWwordsInLine(std::string line);   //2
    void FindAvrgLengthOfWord();
    void FindMostLongWord(std::string potential_long_word);
    void InsertNewWordToMap(std::string a_word);   //
    void InsertExsistWordToMap(std::string a_word);   //
    std::string FixWordAlphaBeit(std::string a_word);
    void InsertWordToMap(std::string);
    void InsertToList(std::string a_word);
    void GatherAllUniqWords();  //3
    void FindMostLongPhrase();
    void FindAvrgLengthPhrase(std::string a_search_for_end_line);
    void FindMostPopularWords();
    void FindMostPopularWordsExclusiv();
    void FindTheLongPhraseWithoutK(std::string a_word);
    bool IsExclusiveWords(std::string);
    std::string ToUpper(std::string a_word);
    void CreateFileRequestes();


    int m_number_of_lines;//v-q1

    int m_number_of_words;//v-q2

    int m_number_of_phrases;//q4
    int m_count_the_chars_from_all_phrases;//q4
    int m_most_long_phrase;//v q4

    std::string m_most_popular_word;//v5
    std::string m_most_popular_word_exclusiv;//v5
    
    int m_most_long_phrase_without_k;//v6
    int m_most_long_phrase_without_k_temp;//v6

    int m_number_of_letters;
    int m_temp_length_of_phrase;
    float m_avrg_length_of_word;
    std::string m_most_long_word;

    std::list<std::string> m_uniq_words;
    std::map<std::string, int> m_map_words;


    PrintToFile m_ptf;
};

#endif //__LEARN_THE_FILE_H__