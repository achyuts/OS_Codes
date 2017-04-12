mutex reader;                 // Controls access to the reader count
mutex writer;                 // Controls access to the database
int reader_count;             // The number of reading processes accessing the data

void reader()
{
    pthread_mutex_lock(&reader);            // gain access to reader_count
    reader_count = reader_count + 1;        // increment the reader_count
    
	if (reader_count == 1)
        pthread_mutex_lock(&writer);        // if this is the first process to read the database,
                                            // a down on db is executed to prevent access to the 
                                            // database by a writing process
    pthread_mutex_unlock(&reader);          // allow other processes to access reader_count
    
	read_db();                             // read the database
    
	pthread_mutex_lock(&reader);           // gain access to reader_count
    reader_count = reader_count - 1;       // decrement reader_count
    if (reader_count == 0)
        pthread_mutex_unlock(&writer);     // if there are no more processes reading from the 
                                           // database, allow writing process to access the data
    pthread_mutex_unlock(&reader);                            // allow other processes to access reader_countuse_data();
                                           // use the data read from the database (non-critical)
}

void writer(char *ch)
{
    pthread_mutex_lock(&writer);           // gain access to the database
    write_db();                            // write information to the database
    pthread_mutex_unlock(&writer);         // release exclusive access to the database
}
