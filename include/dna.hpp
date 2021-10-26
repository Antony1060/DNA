#include<vector>
#include<map>
#include<utility>
#include<cstddef>
#include<cstdint>
#include<cstring>

namespace dna {

    const uint8_t PART_A = 0b00000000;
    const uint8_t PART_T = 0b00000001;
    const uint8_t PART_G = 0b00000010;
    const uint8_t PART_C = 0b00000011;

    class Chain {
        public:
            Chain(): dna_size(0) {}
            Chain(const char* chain): Chain() {
                this->add(chain);
            }
            ~Chain() {
                this->dna_size = 0;
                this->chain.clear();
            }
            size_t size() {
                return this->dna_size;
            }
            void add(const char* parts) {
                for(int i = 0; i < strlen(parts); ++i) {
                    if(this->chain.size() * 4 == this->dna_size)
                        this->chain.push_back(0);
                    size_t cSize = this->chain.size();
                    size_t diff = (cSize * 4) - this->dna_size;
                    uint8_t p = this->cn_map[parts[i]];
                    this->chain[cSize - 1] = this->chain[cSize - 1] | (p << ((diff * 2) - 2));
                    ++this->dna_size;
                }
            }
            std::vector<std::pair<char, char>> full_chain() {
                std::vector<std::pair<char, char>> ret;
                size_t done = 0;
                for(uint8_t &part : this->chain) {
                    for(int i = 6; i >= 0; i -= 2) {
                        if(done >= this->dna_size)
                            goto end;
                        uint8_t n = (part >> i) & 0b00000011;
                        ret.push_back({ this->nc_map[n], this->nc_map[this->opposites[n]] });
                        done++;
                    }
                }
                end:
                return ret;
            }
            std::vector<char> rna_copy() {
                std::vector<char> ret;
                size_t done = 0;
                for(uint8_t &part : this->chain) {
                    for(int i = 6; i >= 0; i -= 2) {
                        if(done >= this->dna_size)
                            goto end;
                        uint8_t n = (part >> i) & 0b00000011;
                        uint8_t o = this->opposites[n];
                        ret.push_back(o == PART_T ? 'U' : this->nc_map[o]);
                        done++;
                    }
                }
                end:
                return ret;
            }
        private:
            inline static std::map<char, uint8_t> cn_map = { { 'T', PART_T }, { 'A', PART_A }, { 'G', PART_G }, { 'C' , PART_C } };
            inline static std::map<uint8_t, char> nc_map = { { PART_T, 'T' }, { PART_A, 'A' }, { PART_G, 'G' }, { PART_C, 'C' } };
            inline static std::map<uint8_t, uint8_t> opposites = { { PART_T, PART_A }, { PART_A, PART_T }, { PART_G, PART_C }, { PART_C, PART_G } };

            size_t dna_size;
            std::vector<uint8_t> chain;

    };

}