#ifndef BUFFER_HPP
#define BUFFER_HPP

class Buffer{
    public:
        Buffer(unsigned int& VAO, float data[], int data_size, int total_elemets);
        Buffer(unsigned int& VAO, float data[], int data_size, unsigned int element_data[], int element_size, int total_elemets);

        void mk_attrib_ptr(int elements, int location, int start_loc);
        
        static unsigned int mk_vao();
        static void bind_vao(unsigned int VAO);

        int total_elemets_i;

        unsigned int VBO;
        unsigned int EBO;
    private:
};


#endif