

#include <iostream>
#include <vector>
using namespace std;

class File
{
public:
    string filename;

    size_t size;

    int partition;
};
class Block
{

    bool occupied = false;

    File file;

public:
    void set_file(File file)
    {
        this->file = file;
        occupied = true;
    }

    string get_file_name()
    {
        return file.filename;
    }

    int get_file_partition_no()
    {
        return file.partition;
    }

    bool is_empty()
    {
        return !occupied;
    }

    void set_empty()
    {
        occupied = false;
    }
};

int get_empty_count(vector<Block> memory)
{
    int sum = 0;
    vector<Block>::iterator slot;

    for (slot = memory.begin();
         slot != memory.end(); slot++)
    {
        sum += (*slot).is_empty();
    }

    return sum;
}

bool file_exists(vector<Block> memory,
                 string name)
{
    vector<Block>::iterator slot;

    for (slot = memory.begin();
         slot != memory.end(); slot++)
    {
        if (!(*slot).is_empty() && (*slot).get_file_name() == name)
        {
            return true;
        }
    }
    return false;
}

void set_contiguous_memory(vector<Block> *memory,
                           vector<int> *index,
                           File file)
{
    bool avail = false;
    int i = 0, count = 0, main_index;
    vector<Block>::iterator slot;

    if (file_exists((*memory),
                    file.filename))
        cout << "File already exists"
             << endl;

    else
    {

        for (slot = (*memory).begin();
             slot != (*memory).end(); slot++)
        {

            if ((*slot).is_empty())
            {
                count++;

                if (count == 1)
                    main_index = i;

                if (count == file.size)
                {
                    avail = true;
                    break;
                }
            }

            else
            {
                count = 0;
            }
            i++;
        }

        if (avail)
        {

            (*index).push_back(main_index);

            count = 0;
            for (int i = main_index;
                 i < main_index + file.size;
                 i++)
            {
                file.partition = count;
                (*memory).at(i).set_file(file);
                count++;
            }
            cout << "File " << file.filename
                 << " has been successfully"
                 << " allocated"
                 << endl;
        }
        else
        {
            cout << "The size of the file is"
                 << " greater than"
                 << endl;
            cout << "the greatest slot available"
                 << " in contiguous memory"
                 << endl;
            cout << "Hence, File "
                 << file.filename
                 << " cannot be allocated"
                 << endl;
        }
    }
}

void delete_contiguous_mem(vector<Block> *memory,
                           vector<int> *index_page,
                           string file)
{
    vector<int>::iterator slot;
    int index, i = 0, main_index;

    if (!file_exists((*memory), file))
        cout << "File does not exist" << endl;
    else
    {

        for (slot = (*index_page).begin();
             slot != (*index_page).end(); slot++)
        {

            if ((*memory).at(*slot).get_file_name() == file)
            {
                index = i;
                main_index = (*slot);
                break;
            }
            i++;
        }

        i = main_index;

        while (i < (*memory).size() && (*memory).at(i).get_file_name() == file && !(*memory).at(i).is_empty())
        {

            (*memory).at(i).set_empty();
            i++;
        }

        (*index_page).erase((*index_page).begin() + index);
        cout << "File " << file
             << " has been successfully deleted"
             << endl;
    }
}

void show_contiguous_index(vector<Block> memory,
                           vector<int> index_page)
{
    int max = 9, i, j;

    vector<Block>::iterator slot;

    string fname;

    for (i = 0; i < index_page.size();
         i++)
    {

        if (memory.at(index_page.at(i))
                .get_file_name()
                .length() > max)
        {

            max = memory.at(index_page
                                .at(i))
                      .get_file_name()
                      .length();

            cout << "+" << string(max + 2, '-')
                 << "+---------------+----"
                 << "---------+-----------"
                 << "-------+\n|"
                 << string(max / 2 + max % 2 - 4,
                           ' ')
                 << "File Name"
                 << string(max / 2 - 3, ' ')
                 << "| Start Address | "
                 << " End Address | Size"
                 << " of the file |\n+"
                 << string(max + 2, '-')
                 << "+---------------+-------"
                 << "------+------------------+"
                 << endl;
        }
    }

    for (i = 0; i < index_page.size();
         i++)
    {
        cout << "|"
             << string(max / 2 + max % 2 - memory.at(index_page.at(i)).get_file_name().length() / 2 - memory.at(index_page.at(i)).get_file_name().length() % 2 + 1,
                       ' ')
             << memory.at(index_page.at(i))
                    .get_file_name()
             << string(max / 2 - memory.at(index_page.at(i)).get_file_name().length() / 2 + 1,
                       ' ')
             << "|"
             << string(8 - to_string(index_page.at(i)).length() / 2 - to_string(index_page.at(i)).length() % 2,
                       ' ')
             << index_page.at(i)
             << string(7 - to_string(index_page
                                         .at(i))
                                   .length() /
                               2,
                       ' ')
             << "|";
        j = index_page
                .at(i);
        fname = memory
                    .at(j)
                    .get_file_name();

        while (j < memory.size() && !memory.at(j).is_empty() && memory.at(j).get_file_name() == fname)
        {
            j++;
        }
        j -= 1;

        cout << string(7 - to_string(j).length() / 2 - to_string(j).length() % 2,
                       ' ')
             << j
             << string(6 - to_string(j)
                                   .length() /
                               2,
                       ' ')
             << "|"
             << string(9 - to_string(j - index_page.at(i) + 1).length() / 2 - to_string(j - index_page.at(i) + 1).length() % 2,
                       ' ')
             << j - index_page.at(i) + 1
             << string(9 - to_string(j - index_page.at(i) + 1)
                                   .length() /
                               2,
                       ' ')
             << "|"
             << endl;
    }
    cout << "+" << string(max + 2, '-')
         << "+---------------+------"
         << "-------+------------------+"
         << endl;
}

void show_contiguous_indexes(vector<Block> memory,
                             vector<int> index_page,
                             string filename)
{
    int index, i;

    vector<int>::iterator slot;

    if (file_exists(memory, filename))
    {
        cout << "File Name = " << filename
             << "\n+------------------+----"
             << "--------------+";

        cout << "\n| Current Location |"
             << " Partition Number |";

        cout << "\n+------------------+-"
             << " -----------------+\n";

        for (slot = index_page.begin();
             slot != index_page.end(); slot++)
        {
            if (memory.at(*slot).get_file_name() == filename)
            {
                index = (*slot);
                break;
            }
        }

        while (index < memory.size() && memory.at(index).get_file_name() == filename && !memory.at(index).is_empty())
        {
            cout << "|"
                 << string(9 - to_string(index).length() / 2 - to_string(index).length() % 2,
                           ' ')
                 << index
                 << string(9 - to_string(index)
                                       .length() /
                                   2,
                           ' ')
                 << "|"

                 << string(9 - to_string(memory.at(index).get_file_partition_no()).length() / 2 - to_string(memory.at(index).get_file_partition_no()).length() % 2,
                           ' ')

                 << memory
                        .at(index)
                        .get_file_partition_no()

                 << string(9 - to_string(memory
                                             .at(index)
                                             .get_file_partition_no())
                                       .length() /
                                   2,
                           ' ')
                 << "|"
                 << endl;
            index++;
        }
        cout << "+------------------+"
             << "------------------+"
             << endl;
    }
    else
        cout << "File does not exist "
             << "in given memory"
             << endl;
}

int main()
{

    vector<Block> memory(16);

    vector<int> index_page;
    File temp;

    cout << "Remaining memory :- "
         << get_empty_count(memory)
         << endl;

    temp.filename = "home.txt";
    temp.size = 5;
    set_contiguous_memory(&memory,
                          &index_page,
                          temp);

    temp.filename = "Report.docx";
    temp.size = 6;
    set_contiguous_memory(&memory,
                          &index_page,
                          temp);

    temp.filename = "new_img.png";
    temp.size = 3;
    set_contiguous_memory(&memory,
                          &index_page,
                          temp);

    temp.filename = "test.cpp";
    temp.size = 2;
    set_contiguous_memory(&memory,
                          &index_page,
                          temp);

    cout << "Remaining memory :- "
         << get_empty_count(memory)
         << endl;

    show_contiguous_index(memory,
                          index_page);

    cout << "Now we will check each partition of";
    cout << " Report.docx and test.cpp before"
         << endl;

    cout << "deleting them to see"
         << " which locations ";

    cout << "are going to be set free"
         << " as our slots"
         << endl;

    show_contiguous_indexes(memory,
                            index_page,
                            "Report.docx");

    show_contiguous_indexes(memory,
                            index_page,
                            "test.cpp");

    delete_contiguous_mem(&memory,
                          &index_page,
                          "Report.docx");

    delete_contiguous_mem(&memory,
                          &index_page,
                          "test.cpp");

    cout << "Remaining memory :- "
         << get_empty_count(memory)
         << endl;

    show_contiguous_index(memory,
                          index_page);

    temp.filename = "hello.jpeg";
    temp.size = 8;
    set_contiguous_memory(&memory,
                          &index_page,
                          temp);

    cout << "Check index page: " << endl;

    show_contiguous_index(memory,
                          index_page);
}
