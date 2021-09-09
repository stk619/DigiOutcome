#pragma once

template< class t, class i = int > struct utl_memory {

	t& operator[ ](i i) {

		return m_memory[i];

	}

protected:

	t* m_memory;
	int m_allocation_count;
	int m_grow_size;

};

template < class t > void destruct(t* memory) {

	memory->~t();

}

template< class t, class a = utl_memory< t > > struct utl_vector {

	t& element(int i) {

		return m_memory[i];

	}

	int count() {

		return m_size;

	}

	void remove_all() {

		for (int i = m_size; --i >= 0; )
			destruct(&element(i));

		m_size = 0;

	}

protected:

	a m_memory;
	int m_size;
	t* m_elements;

};