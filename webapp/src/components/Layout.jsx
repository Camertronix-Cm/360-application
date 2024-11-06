<<<<<<< HEAD


import PropTypes from 'prop-types';
import Header from './Header';
import Footer from './Footer';


export const Layout = ({ children }) => {
 

return (
    <div className='container mx-auto px-4 '>
    <Header />

      {children}

    <Footer />
    </div>
  );
  
}
Layout.propTypes = {
    children: PropTypes.node.isRequired,
};



=======
 
import PropTypes from 'prop-types';

const Layout = ({ children }) => {
    return (
        <div className="layout">
            <header>
                <h1>My Application</h1>
            </header>
            <main>
                {children}
            </main>
            <footer>
                <p>&copy; 2023 My Application</p>
            </footer>
        </div>
    );
};
Layout.propTypes = {
    children: PropTypes.node.isRequired,
};
 
export default Layout;
>>>>>>> 9a46186bb9e48daea7d74dd392900573f17c3a51
