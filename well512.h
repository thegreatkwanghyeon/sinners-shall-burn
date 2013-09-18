#ifndef __well512__
#define __well512__

class Well512{
	private : 

		unsigned int state[16];
		unsigned int index;

	public : 

		Well512(){
			index = 0;
			for (unsigned int i = 0; i < 16; i++)
			{
				state[i] = i;
			}
		}

		~Well512(){}

		unsigned int Next(int minValue, int maxValue){
			return (unsigned int)((Next() % (maxValue - minValue)) + minValue);
		}

		unsigned int Next(unsigned int maxValue){
			return Next() % maxValue;
		}

		unsigned int Next(){
			unsigned int a, b, c, d;

			a = state[index];
			c = state[(index + 13) & 15];
			b = a ^ c ^ (a << 16) ^ (c << 15);
			c = state[(index + 9) & 15];
			c ^= (c >> 11);
			a = state[index] = b ^ c;
			d = a ^ ((a << 5) & 0xda442d24U);
			index = (index + 15) & 15;
			a = state[index];
			state[index] = a ^ b ^ d ^ (a << 2) ^ (b << 18) ^ (c << 28);

			return state[index];
		}
};

#endif
