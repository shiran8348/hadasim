#include "LearnTheFile.h"

#include <algorithm>
#include <string>


LearnTheFile::LearnTheFile(std::string a_name_of_file, std::string a_name_output_file) :
m_number_of_words(0),
m_number_of_lines(0),
m_number_of_letters(0),
m_most_long_word(""),
m_avrg_length_of_word(0.0),
m_file(a_name_of_file),
m_ptf(a_name_output_file)
{

    try {
        if (m_file.fail()) {
            throw "FAIL TO OPENF FILE !\n";
        }
        FindNumOfLines();
        FindAvrgLengthOfWord();
        FindAvrgLengthOfWord();
        GatherAllUniqWords();

        FindMostPopularWords();
        FindMostPopularWordsExclusiv();
        m_file.close();

    }
    catch (... ) {
        if (m_file.is_open()) {
            m_file.close();
            std::cout << "error detected: " << "\n";
            exit(0);
        }
        else {
            std::cout << "COULD NOT OPEN FILE  /  FILE NOT EXIST: "  << "\n";
            exit(0);
        }
    }
}

void LearnTheFile::FindNumOfLines() {
    int number_of_lines = 0;
    std::string line;
    while (std::getline(m_file, line))
    {
        ++number_of_lines;
        FindNumOfWwordsInLine(line);
    }
    m_number_of_lines = number_of_lines;
}
void LearnTheFile::FindNumOfWwordsInLine(std::string line) {
    int number_of_words = 0;
    std::string word = "";
    char letter = ' ';

    for (int i = 0; i < line.length(); ++i) {
        letter = line.at(i);
        if ((letter == ' ' || letter == '\0' || letter == '\t' || letter == '\n')  && (word != "")) {
            if (!(word.at(0) == ' ' || word.at(0) == '0' || word.at(0) == '\t' || word.at(0) == '\n')) {
                
                word = FixWordAlphaBeit(word);

                if (word != "") {
                    ++number_of_words;
                    m_number_of_letters += int(word.length());
                    FindMostLongWord(word);
                    FindTheLongPhraseWithoutK(word);
                    InsertWordToMap(word);
                }
            }
            word = "";
        }
        else if (letter != ' ') {
            word += (letter);
        }
    }
    if ((word != "" ) && !(word.at(0) == ' ' || word.at(0) == '0' || word.at(0) == '\t' || word.at(0) == '\n')) {
        word = FixWordAlphaBeit(word);
        if (word != "") {
            number_of_words++;
            m_number_of_letters += int(word.length());
            FindMostLongWord(word);
            FindTheLongPhraseWithoutK(word);
            InsertWordToMap(word);
        }
    } 
    m_number_of_words += number_of_words;
}

void LearnTheFile::InsertNewWordToMap(std::string a_word) {
    m_map_words.insert({a_word, 1});
}
void LearnTheFile::InsertExsistWordToMap(std::string a_word) {
    m_map_words[a_word] += 1 ;
}
std::string LearnTheFile::FixWordAlphaBeit(std::string a_word) {
     if (a_word.at(a_word.length()-1) == ';' ||a_word.at(a_word.length() - 1 )== '.') {
        FindAvrgLengthPhrase(a_word);
        do { a_word.pop_back(); } while (a_word.at(a_word.length() - 1) == '.');
    }
     m_temp_length_of_phrase += int(a_word.length());
     m_count_the_chars_from_all_phrases += int(a_word.length());
    while (!(isalpha(a_word.at(a_word.length() - 1))) && !(isdigit((a_word.at(a_word.length() - 1))))) {
        a_word.pop_back();
    }
    while (!(isalpha(a_word.at(a_word.length() - 1))) && !(isdigit((a_word.at(a_word.length() - 1))))) {
        a_word.erase(0,1);
    }
    return a_word;
}
void LearnTheFile::InsertWordToMap(std::string a_word) {
    //m_count_the_chars_from_all_phrases += a_word.length();
    auto itr = m_map_words.find(a_word);
    if (itr == m_map_words.end()) {
        InsertNewWordToMap(a_word);
    }
    else {
        InsertExsistWordToMap(a_word);
    }
}
void LearnTheFile::PrintAllWords() {
    std::for_each(m_map_words.begin(),
        m_map_words.end(),
        [](const std::pair<std::string, int>& p) {
            std::cout << "{" << p.first << ": " << p.second << "}\n";
        });
}

void LearnTheFile::PrintAllUniqWords() {
    for (auto const& uniq_word : m_uniq_words) {
        std::cout << "\t" + uniq_word + "\n";
    }
}
void LearnTheFile::GatherAllUniqWords() {
    std::for_each(m_map_words.begin(),
        m_map_words.end(),
        [&](const std::pair<std::string, int>& p) {
            if (p.second == 1) {
                InsertToList(p.first);
                
            }
        });
                
}
void LearnTheFile::InsertToList(std::string a_word) {
    m_uniq_words.push_back(a_word);
}

void LearnTheFile::FindAvrgLengthOfWord() {
    float avrg_length_of_word = 0.0;
    avrg_length_of_word = ( m_number_of_letters/ float(m_number_of_words) ) ;
    m_avrg_length_of_word = avrg_length_of_word;
}
void LearnTheFile::FindMostLongWord(std::string potential_long_word) {
    if (potential_long_word.length() > m_most_long_word.length()) {
        m_most_long_word = potential_long_word;
    }
}
void LearnTheFile::FindMostLongPhrase() {
    if (m_temp_length_of_phrase > m_most_long_phrase) {
        m_most_long_phrase = m_temp_length_of_phrase;
    }
    m_temp_length_of_phrase = 0;
}
void LearnTheFile::FindAvrgLengthPhrase(std::string a_search_for_end_line) {
    FindMostLongPhrase();    
    m_number_of_phrases++;
}

void LearnTheFile::FindMostPopularWords() {
    std::string key_most_popular_word = "";
    int value_most_popular_word = 0;

    std::for_each(m_map_words.begin(),
        m_map_words.end(),
        [&](const std::pair<std::string, int>& p) {
            if (p.second > value_most_popular_word) {
                value_most_popular_word = p.second;
                key_most_popular_word = p.first;
            }
        });
    m_most_popular_word = key_most_popular_word;
}

void LearnTheFile::FindMostPopularWordsExclusiv() {
    std::string key_most_popular_word = "";
    int value_most_popular_word = 0;

    std::for_each(m_map_words.begin(),
        m_map_words.end(),
        [&](const std::pair<std::string, int>& word_most_pop) {

            if( (word_most_pop.second > value_most_popular_word) // && do in arr
                && (IsExclusiveWords(word_most_pop.first))) {
                value_most_popular_word = word_most_pop.second;
                key_most_popular_word = word_most_pop.first;
            }
        });
    m_most_popular_word_exclusiv = key_most_popular_word;
}

void LearnTheFile::FindTheLongPhraseWithoutK(std::string a_word) {
    if ((a_word.find('k') != std::string::npos) || a_word.find('K') != std::string::npos) {
        m_most_long_phrase_without_k_temp = 0;
    }
    else {
        m_most_long_phrase_without_k_temp++;
        if (m_most_long_phrase_without_k_temp > m_most_long_phrase_without_k) {
            m_most_long_phrase_without_k = m_most_long_phrase_without_k_temp;
        }
    }
    
}

bool LearnTheFile::IsExclusiveWords(std::string a_word) {
    int size = EXCLUSIVE_WORD->length();
    std::string word = ToUpper(a_word);

    for (int i = 0; i < size; i++) {
        if ((EXCLUSIVE_WORD[i] == word)) {
            return false;
        }
        return true;
    }
}

std::string LearnTheFile::ToUpper(std::string a_word) {
    std::string word;
    int size = a_word.length();
    for (int x = 0; x < size; x++)
        word += (toupper(a_word[x]));
    return word;
}


void LearnTheFile::CreateFileRequestes() {

    std::string request_saperated = "\n---------------------\n";
    m_ptf.AddRequest("num of lines: " + (std::to_string(GetNumofLines())) + request_saperated);
    m_ptf.AddRequest("num of words:" + (std::to_string(GetNumOfWords())) + request_saperated);
    m_ptf.AddRequest("UNIQ WORDS :");
    for (auto const& uniq_word : m_uniq_words) {
        m_ptf.AddRequest("\t" + uniq_word);
    }
    m_ptf.AddRequest(request_saperated + "avrg number LETTERS IN phrases: " + (std::to_string(GetAvrgLenghtOfPhrase()))+ " letters");
    m_ptf.AddRequest(request_saperated + "number of letters in the longets phrases: " + (std::to_string(GetNumOfMostLongPhrase())) + " letters");
    m_ptf.AddRequest(request_saperated + "MOST POULAR WORD: " + (GetMostPopularWord()));
    m_ptf.AddRequest(request_saperated + "MOST POULAR WORD EXCLUSIV: " + ((GetMostPopularWordExclusive())));
    m_ptf.AddRequest(request_saperated + "MOST long phrase with no K: " + (std::to_string(GetTheLongPhraseWithoutK())));
}

void LearnTheFile::makeFileRequests() {
    CreateFileRequestes();
    m_ptf.MakeRequestsFile();
    m_ptf.CloseTheFile();
}