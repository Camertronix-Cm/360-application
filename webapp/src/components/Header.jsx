import { Link } from 'react-router-dom';
import logo from '../assets/logo.png';

const Header = () => {
    return (
        <div className="navbar   bg-neutral text-primary-content rounded-box my-2">
            <div className="navbar-start">
                <div className="dropdown">
                    <div tabIndex={0} role="button" className="btn btn-ghost lg:hidden">
                        <svg
                            xmlns="http://www.w3.org/2000/svg"
                            className="h-5 w-5"
                            fill="none"
                            viewBox="0 0 24 24"
                            stroke="currentColor">
                            <path
                                strokeLinecap="round"
                                strokeLinejoin="round"
                                strokeWidth="2"
                                d="M4 6h16M4 12h8m-8 6h16" />
                        </svg>
                    </div>
                    <ul
                        tabIndex={0}
                        className="menu menu-sm dropdown-content bg-base-100 rounded-box z-[1] mt-3 w-52 p-2 shadow">
                        <li><a>Item 1</a></li>
                        <li>
                            <a>Parent</a>
                            <ul className="p-2">
                                <li><a>Submenu 1</a></li>
                                <li><a>Submenu 2</a></li>
                            </ul>
                        </li>
                        <li><a>Item 3</a></li>
                    </ul>
                </div>
                 
                <Link className='pl-2' to="/"><img className='w-28' src={logo} alt="" /></Link>
                
               
                {/* <a className="btn btn-neutral text-2xl"><img className='w-20' src={logo} alt="" /></a> */}
            </div>
            <div className="navbar-center hidden lg:flex">
                <ul className="menu menu-horizontal px-1">
                    <li><Link to="/">Home </Link></li>
                    <li><Link to="/360">360 Streamer</Link></li>
                  <li><Link to="/about">About</Link></li>
                    <li><Link to="/blogs">Blogs & Experiments</Link></li>
                   

                </ul>
            </div>
            <div className="navbar-end">
                <a className="btn">Contact</a>
            </div>
        </div>

    );
};

export default Header;